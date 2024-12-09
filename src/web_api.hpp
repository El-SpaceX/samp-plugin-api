#pragma once

using PublicPtr = std::shared_ptr<ptl::Public>;

class WebAPI
{
public:
	enum class HTTP_METHODS : char
	{
		M_GET,
		M_POST,
		M_PUT,
		M_PATCH,
		M_DELETE
	};

	WebAPI() {};
	~WebAPI() {};

	inline httplib::Request* GetRequest() const { return m_pRequest; }
	inline httplib::Response* GetResponse() const { return m_pResponse; }

	bool Run(const std::string& host, uint16_t port);
	bool Stop();
	inline bool IsRunning() const;
	bool AddRoute(HTTP_METHODS method, const std::string& pattern, PublicPtr callback);

private:
	std::string m_szIP{ "localhost" };
	uint16_t m_iPort{ 5000 };
	httplib::Server m_webSvr;
	std::thread m_svrThread;


	httplib::Request* m_pRequest{ nullptr };
	httplib::Response* m_pResponse{ nullptr };

	inline void SetCallbackPointers(httplib::Request* req, httplib::Response* res) { m_pRequest = req; m_pResponse = res; }
};
