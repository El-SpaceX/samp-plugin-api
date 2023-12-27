#include "script.hpp"


//server manager
cell Script::n_Start(std::string host, cell port)
{
	return api.Start(host, port);
}

cell Script::n_Stop()
{
	return api.Stop();
}

cell Script::n_IsRunning()
{
	return api.IsRunning();
}

cell Script::n_AddGet(std::string pattern, std::string callback)
{
	if (pattern.empty())
	{
		Log("The pattern is empty.");
		return 0;
	}

	if (callback.empty())
	{
		Log("The callback is empty.");
		return 0;
	}

	PublicPtr pCallback = MakePublic(callback);
	if (!pCallback->Exists())
	{
		Log("The %s callback does not exists.", callback.c_str());
		return 0;
	}

	api.AddGet(pattern, pCallback);
	return 1;
}

//token | rate limit per minute

cell Script::n_TokenExists(std::string token)
{
	return api.TokenExists(token);
}

cell Script::n_AddToken(std::string token, cell ratelimit)
{
	if (token.empty())
		return 0;

	api.AddToken(token, ratelimit);
	return 1;
}
cell Script::n_RemoveToken(std::string token)
{
	api.RemoveToken(token);
	return 1;
}

cell Script::n_GetRateLimit(std::string token)
{
	const auto tokenInfo = api.GetTokenInfo(token);
	if (!tokenInfo)
		return -1;

	return tokenInfo->iRatelimit;

}
cell Script::n_SetRateLimit(std::string token, cell ratelimit)
{
	const auto tokenInfo = api.GetTokenInfo(token);
	if (!tokenInfo)
		return false;

	tokenInfo->iRatelimit = (ratelimit < 0) ? -1 :ratelimit;
	return true;
}

cell Script::n_ToggleTokenRequired(cell toggle)
{
	api.ToggleTokenRequired(toggle);
	return 1;
}

cell Script::n_IsRequiredToken()
{
	return api.IsTokenRequired();
}



//response manager
cell Script::n_SetContent(std::string content)
{
	const auto response = api.GetResponse();
	if (!response)
		return 0;

	response->set_content(content, "text/plain");
	return 1;
}

cell Script::n_SetContentHTML(std::string html)
{
	const auto response = api.GetResponse();
	if (!response)
		return 0;

	response->set_content(html, "text/html");
	return 1;
}


//params

cell Script::n_HasParam(std::string param)
{
	const auto request = api.GetRequest();
	if (!request) 
		return false;

	return request->has_param(param);
}

cell Script::n_GetParam(std::string param, cell* output, cell size)
{
	const auto request = api.GetRequest();
	if (!request || !request->has_param(param))
	{
		SetString(output, "", size);
		return false;
	}
	SetString(output, request->get_param_value(param), size);
	return true;
}

cell Script::n_GetParamInt(std::string param)
{
	const auto request = api.GetRequest();
	if (!request || !request->has_param(param))
		return std::numeric_limits<cell>::min();

	try
	{
		return std::stoi(request->get_param_value(param));
	}
	catch (...)
	{
	}

	return std::numeric_limits<cell>::min();
}

cell Script::n_GetParamFloat(std::string param)
{
	float value = std::numeric_limits<float>::min();
	const auto request = api.GetRequest();
	if (!request || !request->has_param(param))
		return amx_ftoc(value);

	try
	{
		value = std::stof(request->get_param_value(param));
	}
	catch (...)
	{
	}

	return amx_ftoc(value);
}

cell Script::n_GetParamBool(std::string param)
{
	return static_cast<bool>(this->n_GetParamInt(param));
}

cell Script::n_HasPathParam(std::string param)
{
	const auto request = api.GetRequest();
	if (!request)
		return false;


	return (request->path_params.find(param) != request->path_params.end());
}

cell Script::n_GetPathParam(std::string param, cell* output, cell size)
{
	const auto request = api.GetRequest();
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

cell Script::n_GetPathParamInt(std::string param)
{
	const auto request = api.GetRequest();
	if (!request)
		return std::numeric_limits<cell>::min();


	if (request->path_params.find(param) == request->path_params.end())
		return std::numeric_limits<cell>::min();

	try
	{
		return std::stoi(request->path_params.at(param));
	}
	catch (...)
	{
	}

	return std::numeric_limits<cell>::min();
}

cell Script::n_GetPathParamFloat(std::string param)
{
	float value = std::numeric_limits<float>::min();;
	const auto request = api.GetRequest();
	if (!request)
		return amx_ftoc(value);


	if (request->path_params.find(param) == request->path_params.end())
		return amx_ftoc(value);

	try
	{
		value = std::stof(request->path_params.at(param));
	}
	catch (...)
	{
	}

	return amx_ftoc(value);
}

cell Script::n_GetPathParamBool(std::string param)
{
	return static_cast<bool>(this->n_GetPathParamInt(param));
}