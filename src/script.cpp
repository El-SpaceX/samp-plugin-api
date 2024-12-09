#include "main.hpp"


// WebAPI manager
cell Script::WAPI_Run(std::string host, int port)
{
	return webAPI.Run(host, port);
}
cell Script::WAPI_Stop()
{
	return webAPI.Stop();
}
cell Script::WAPI_IsRunning()
{
	return webAPI.IsRunning();
}

cell Script::WAPI_AddRoute(int method, std::string pattern, std::string callback)
{

	if (callback.empty())
	{
		Log("You passed an empty callback");
		return 0;
	}

	PublicPtr pCallback = MakePublic(callback);
	if (!pCallback->Exists())
	{
		Log("Callback \"%s\" does not exist.", callback.c_str());
		return 0;
	}


	return webAPI.AddRoute(static_cast<WebAPI::HTTP_METHODS>(method), pattern, pCallback);
}

cell Script::WAPI_SetContent(std::string content, std::string content_type)
{
	const auto response = webAPI.GetResponse();
	if (!response)
		return 0;

	response->set_content(content, content_type);
	return 1;
}


//request-headers

cell Script::WAPI_HasHeader(std::string header)
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return 0;

	return request->has_header(header);
}

cell Script::WAPI_GetHeader(std::string header, cell* output, cell size)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_header(header))
		return 0;

	SetString(output, request->get_header_value(header), size);
	return 1;
}

cell Script::WAPI_GetHeaderInt(std::string header)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_header(header))
		return 0;
	
	return utils::StringToAmxCell(request->get_header_value(header));
}

cell Script::WAPI_GetHeaderFloat(std::string header)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_header(header))
		return amx_ftoc(utils::floatMin);

	return utils::StringToAmxFloat(request->get_header_value(header));
}

//url-params
cell Script::WAPI_HasParam(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return 0;

	return request->has_param(param);
}

cell Script::WAPI_GetParam(std::string param, cell* output, cell size)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_param(param))
		return 0;

	SetString(output, request->get_param_value(param), size);
	return 1;
}

cell Script::WAPI_GetParamInt(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_param(param))
		return utils::cellMin;
	
	return utils::StringToAmxCell(request->get_param_value(param));
}

cell Script::WAPI_GetParamFloat(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request || !request->has_param(param))
		return amx_ftoc(utils::floatMin);

	return utils::StringToAmxFloat(request->get_param_value(param));
}

//path-params -> http://host.com/users/:id
cell Script::WAPI_HasPathParam(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return false;

	return (request->path_params.find(param) != request->path_params.end());
}

cell Script::WAPI_GetPathParam(std::string param, cell* output, cell size)
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return 0;

	if (request->path_params.find(param) == request->path_params.end())
	{
		SetString(output, "", size);
		return 0;
	}

	SetString(output, request->path_params.at(param), size);
	return 1;
}

cell Script::WAPI_GetPathParamInt(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request || request->path_params.find(param) == request->path_params.end())
		return utils::cellMin;

	return utils::StringToAmxCell(request->path_params.at(param));
}

cell Script::WAPI_GetPathParamFloat(std::string param)
{
	const auto request = webAPI.GetRequest();
	if (!request || request->path_params.find(param) == request->path_params.end())
		return amx_ftoc(utils::floatMin);

	return utils::StringToAmxFloat(request->path_params.at(param));
}

//request body
cell Script::WAPI_GetBodySize()
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return 0;

	return request->body.length();
}

cell Script::WAPI_GetContentBody(cell* output, cell size)
{
	const auto request = webAPI.GetRequest();
	if (!request)
		return 0;

	SetString(output, request->body, size);
	return 1;
}