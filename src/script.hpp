#pragma once


class Script : public ptl::AbstractScript<Script>
{
public:
	cell WAPI_Run(std::string host, int port);
	cell WAPI_Stop();
	cell WAPI_IsRunning();
	cell WAPI_AddRoute(int method, std::string pattern, std::string callback);
	
	cell WAPI_SetContent(std::string content, std::string content_type);
	
	//headers
	cell WAPI_HasHeader(std::string header);
	cell WAPI_GetHeader(std::string header, cell* output, cell size);
	cell WAPI_GetHeaderInt(std::string header);
	cell WAPI_GetHeaderFloat(std::string header);

	//url params
	cell WAPI_HasParam(std::string param);
	cell WAPI_GetParam(std::string param, cell* output, cell size);
	cell WAPI_GetParamInt(std::string param);
	cell WAPI_GetParamFloat(std::string param);

	//path params
	cell WAPI_HasPathParam(std::string param);
	cell WAPI_GetPathParam(std::string param, cell* output, cell size);
	cell WAPI_GetPathParamInt(std::string param);
	cell WAPI_GetPathParamFloat(std::string param);

	//body request
	cell WAPI_GetBodySize();
	cell WAPI_GetContentBody(cell* output, cell size);

private:
};
