#ifndef _API_H_
#define _API_H_

#include <cpp-httplib/httplib.h>
#include <samp-ptl/ptl.h>
#include <chrono>
#include <string>


using namespace httplib;
using PublicPtr = std::shared_ptr<ptl::Public>;


class API 
{
private:
	Server server;
	std::string sIP = "localhost";
	unsigned short iPort = 80;
	Request* pReqTemp = nullptr;
	Response* pResTemp = nullptr;
	std::thread serverThread;


	//token
	struct TokenInfo
	{
		int iRatelimit;
		unsigned int iRequests;
		std::chrono::steady_clock::time_point lastTime;
	};
	std::unordered_map<std::string, TokenInfo> tokens;
	bool bRequiredToken = false;

public:
	enum class TokenVerify : char
	{
		OK,
		RATE_LIMIT_EXCEEDED,
		TOKEN_INVALID
	};

	TokenVerify CheckToken(const std::string& token);
	TokenInfo* GetTokenInfo(const std::string& token);
	inline void AddToken(const std::string& token, int ratelimit) 
	{ 
		this->tokens.insert(std::pair(token, TokenInfo{ratelimit, 0, std::chrono::steady_clock::now()})); 
	}
	inline void RemoveToken(const std::string& token) 
	{ 
		this->tokens.erase(token); 
	}
	inline void ToggleTokenRequired(bool toggle) 
	{ 
		this->bRequiredToken = true; 
	}
	inline bool IsTokenRequired() const 
	{ 
		return this->bRequiredToken; 
	}
	inline bool TokenExists(const std::string& token) const 
	{ 
		return (this->tokens.find(token) != this->tokens.end()); 
	}

	inline void SetRequest(Request* request) { this->pReqTemp = request; }
	inline void SetResponse(Response* response) { this->pResTemp = response; }

	inline Request* GetRequest() const { return this->pReqTemp; }
	inline Response* GetResponse() const { return this->pResTemp; }

	inline bool IsRunning() const { return this->server.is_running(); }

	bool Start(const std::string& host, unsigned short port);
	bool Stop();

	bool AddGet(const std::string& pattern, PublicPtr& callbackPointer);
	bool AddPost(const std::string& pattern, PublicPtr& callbackPointer);
};

extern API api;
#endif

