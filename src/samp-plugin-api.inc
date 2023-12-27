/*
@author: El-SpaceX
@github: https://github.com/El-SpaceX
*/

#if defined API_PLUGIN_INCLUDED
    #endinput
#endif
#define API_PLUGIN_INCLUDED

#define API_CALLBACK%0(%1) forward%0(%1); public%0(%1)


//handler/callbacks
native API_AddGet(const pattern[], const callback[]);

//server
native API_Start(const ip[], port);
native API_Stop();
native bool:API_IsRunning();

//response content
native API_SetContent(const content[]);
native API_SetContentHTML(const HTML[]);

//token | rate limit per minute
native API_TokenExists(const token[]);
native API_AddToken(const token[], ratelimit = -1); //-1 == no limit
native API_RemoveToken(const token[]);
native API_GetRateLimit(const token[]);
native API_SetRateLimit(const token[], ratelimit);
native API_ToggleRequiredToken(bool:toggle);
native bool:API_IsRequiredToken();

//params
native API_HasParam(const param[]);
native API_GetParamEx(const param[], output[], size = sizeof output);
native API_GetParamInt(const param[]);
native API_GetParamFloat(const param[]);
native bool:API_GetParamBool(const param);


//path params
native API_HasPathParam(const param[]);
native API_GetPathParamEx(const param[], output[], size = sizeof output);
native API_GetPathParamInt(const param[]);
native API_GetPathParamFloat(const param[]);
native bool:API_GetPathParamBool(const param);


stock API_GetPathParam(const param[])
{
    static param_str[256];
    API_GetPathParamEx(param, param_str, sizeof param_str);
    return param_str;
}

stock API_GetParam(const param[])
{
    static param_str[256];
    API_GetParamEx(param, param_str, sizeof param_str);
    return param_str;
}