#ifndef _NATIVES_H_
#define _NATIVES_H_

#include <samp-ptl/ptl.h>
#include "api.hpp"

using Token = std::string;

class Script : public ptl::AbstractScript<Script>
{
public:
	//server manager
	cell n_Start(std::string host, cell port);
	cell n_Stop();
	cell n_IsRunning();
	cell n_AddGet(std::string pattern, std::string callback);
	cell n_AddPost(std::string pattern, std::string callback);

	//response content
	cell n_SetContent(std::string content);
	cell n_SetContentHTML(std::string html);
	cell n_SetContentJSON(std::string json);

	//header
	cell n_HasHeader(std::string header);
	cell n_GetHeader(std::string header, cell* output, cell size);
	cell n_GetHeaderInt(std::string header);
	cell n_GetHeaderFloat(std::string header);
	cell n_GetHeaderBool(std::string header);

	//body
	cell n_GetContentBody(cell* output, cell size);

	//token | ratelimit per minute
	cell n_IsRequiredToken();
	cell n_ToggleTokenRequired(cell toggle);
	cell n_TokenExists(std::string token);

	cell n_AddToken(std::string token, cell ratelimit);
	cell n_RemoveToken(std::string token);
	cell n_GetRateLimit(std::string token);
	cell n_SetRateLimit(std::string token, cell ratelimit);

	//params
	cell n_HasParam(std::string param);
	cell n_GetParam(std::string param, cell* output, cell size);
	cell n_GetParamInt(std::string param);
	cell n_GetParamFloat(std::string param);
	cell n_GetParamBool(std::string param);


	//path params
	cell n_HasPathParam(std::string param);
	cell n_GetPathParam(std::string param, cell* output, cell size);
	cell n_GetPathParamInt(std::string param);
	cell n_GetPathParamFloat(std::string param);
	cell n_GetPathParamBool(std::string param);
private:
};
#endif
