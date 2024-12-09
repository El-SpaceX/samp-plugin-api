#include "main.hpp"

bool WebAPI::Run(const std::string& host, uint16_t port)
{
	if (IsRunning())
	{
		return false;
	}

	m_szIP = host;
	m_iPort = port;

	m_svrThread = std::thread([this]() {
		Plugin::Get().Log("Starting API (%s:%d)", m_szIP.c_str(), m_iPort);
		m_webSvr.listen(m_szIP, m_iPort);
	});
	return true;
}

bool WebAPI::Stop() 
{
	if (!IsRunning())
	{
		return false;
	}

	m_webSvr.stop();
	Plugin::Get().Log("API closed successfully.");
	return true;
}

bool WebAPI::IsRunning() const 
{
	return m_webSvr.is_running();
}

bool WebAPI::AddRoute(HTTP_METHODS method, const std::string& pattern, PublicPtr callback)
{
	auto func = [=](const httplib::Request& request, httplib::Response& response) {
		this->SetCallbackPointers(const_cast<httplib::Request*>(&request), &response);

		const cell ret = callback->Exec(request.remote_addr, request.remote_port);
		response.status = ret;

		this->SetCallbackPointers(nullptr, nullptr);
		return;
	};

	switch (method)
	{
	case HTTP_METHODS::M_GET:
		m_webSvr.Get(pattern, func);
		return true;
	case HTTP_METHODS::M_POST:
		m_webSvr.Post(pattern, func);
		return true;
	case HTTP_METHODS::M_PUT:
		m_webSvr.Put(pattern, func);
		return true;
	case HTTP_METHODS::M_PATCH:
		m_webSvr.Patch(pattern, func);
		return true;
	case HTTP_METHODS::M_DELETE:
		m_webSvr.Delete(pattern, func);
		return true;
	default:
		Plugin::Get().Log("Invalid method on route \"%s\".", pattern.c_str());
		return false;;
	}

	return false;
}