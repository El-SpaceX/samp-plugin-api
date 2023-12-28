#include "api.hpp"
#include "plugin.hpp"

API api;

bool API::Start(const std::string& host, unsigned short port)
{
	if (this->IsRunning())
		return false;

	this->sIP = host;
	this->iPort = port;

	this->serverThread = std::thread([&]() {
		Plugin::Get().Log("Starting API %s:%d", this->sIP.c_str(), this->iPort);
		server.listen(this->sIP, this->iPort);
	});

	return true;
}

bool API::Stop()
{
	if (!this->IsRunning())
		return false;

	this->Stop();
	Plugin::Get().Log("API closed.");
	return true;
}


bool API::AddGet(const std::string& pattern, PublicPtr& callbackPointer)
{
	if (!callbackPointer->Exists())
		return false;

	this->server.Get(pattern, [=](const Request& request, Response& response) {
		if (this->bRequiredToken)
		{
			if (!request.has_header("Authorization"))
			{
				response.status = 403;
				return;
			}

			const auto status = this->CheckToken(request.get_header_value("Authorization"));
			if (status != TokenVerify::OK)
			{
				//429 - Sent too many requests
				//403 - Forbidden
				response.status = (status == TokenVerify::RATE_LIMIT_EXCEEDED) ? 429 : 403;
				return;
			}
		}


		this->SetRequest(const_cast<Request*>(&request));
		this->SetResponse(&response);


		const cell ret = callbackPointer->Exec(request.remote_addr, request.remote_port);
		this->GetResponse()->status = ret;

		this->SetRequest(nullptr);
		this->SetResponse(nullptr);
		return;
	});

	return true;
}


bool API::AddPost(const std::string& pattern, PublicPtr& callbackPointer)
{
	if (!callbackPointer->Exists())
		return false;

	this->server.Post(pattern, [=](const Request& request, Response& response) {
		if (this->bRequiredToken)
		{
			if (!request.has_header("Authorization"))
			{
				response.status = 403;
				return;
			}

			const auto status = this->CheckToken(request.get_header_value("Authorization"));
			if (status != TokenVerify::OK)
			{
				//429 - Sent too many requests
				//403 - Forbidden
				response.status = (status == TokenVerify::RATE_LIMIT_EXCEEDED) ? 429 : 403;
				return;
			}
		}


		this->SetRequest(const_cast<Request*>(&request));
		this->SetResponse(&response);


		const cell ret = callbackPointer->Exec(request.remote_addr, request.remote_port);
		this->GetResponse()->status = ret;

		this->SetRequest(nullptr);
		this->SetResponse(nullptr);
		return;
		});

	return true;
}


API::TokenVerify API::CheckToken(const std::string& token)
{
	if (token.empty())
		return TokenVerify::TOKEN_INVALID;

	const auto it = this->tokens.find(token);
	if (it == this->tokens.end())
		return TokenVerify::TOKEN_INVALID;

	auto& tokenInfo = it->second;
	
	if (tokenInfo.iRatelimit < 0)
		return TokenVerify::OK;

	using namespace std::chrono;
	const auto currentTime = steady_clock::now();

	if (duration_cast<seconds>(currentTime - tokenInfo.lastTime).count() > 60)
	{
		tokenInfo.lastTime = currentTime;
		tokenInfo.iRequests = 1;
	}

	else if (++tokenInfo.iRequests > static_cast<unsigned int>(tokenInfo.iRatelimit))
	{
		return TokenVerify::RATE_LIMIT_EXCEEDED;
	}

	return TokenVerify::OK;
}

API::TokenInfo* API::GetTokenInfo(const std::string& token)
{
	const auto it = this->tokens.find(token);
	if (it == tokens.end())
		return nullptr;

	return &it->second;
}