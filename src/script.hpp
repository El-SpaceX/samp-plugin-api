#ifndef _NATIVES_H_
#define _NATIVES_H_

#include <samp-ptl/ptl.h>
#include "api.hpp"

using Token = std::string;

class Script : public ptl::AbstractScript<Script> {
public:

    // handle/callbacks
    cell n_RegisterHandle(const std::string pattern, const std::string callback);
    cell n_DeleteHandle(const std::string pattern);


    // server manager
    cell n_StartServer(std::string ip, int port);
    cell n_StopServer();
    cell n_IsServerRunning();

    // response content
    cell n_SetContent(std::string content);
    cell n_SetContentHTML(std::string html);

    // token
    cell n_AddToken(Token token, int ratelimit);
    cell n_ExistsToken(Token token);
    cell n_DeleteToken(Token token);
    cell n_ToggleRequiredToken(int toggle);
    cell n_GetRequiredToken();


    //ratelimit
    cell Script::n_SetRateLimit(Token token, int ratelimit);
    cell Script::n_GetRateLimit(Token token);


    // params
    cell n_HasParam(std::string params_key);
    cell n_GetParam(std::string params_key, cell* output, int size);
    cell n_GetParamInt(std::string key);
    cell n_GetParamFloat(std::string key);
    cell n_GetNumParams();
private:

};
#endif
