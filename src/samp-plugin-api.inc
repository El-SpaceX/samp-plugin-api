/*
@author: El-SpaceX
@github: https://github.com/El-SpaceX
*/

#if defined API_PLUGIN_INCLUDED
    #endinput
#endif
#define API_PLUGIN_INCLUDED


//handler/callbacks
native RegisterHandle(const pattern[], const callback[]); //method GET
native DeleteHandle(const pattern[]);

//server
native StartServer(const ip[], port);
native StopServer();
native bool:IsServerRunning();

//response content
native SetContent(const content[]);
native SetContentHTML(const HTML[]);

//params
native GetNumParams();
native bool:HasParam(const key[]);
native GetParam(const key[], output[], length = sizeof(output));
native GetParamInt(const key[]);
native Float:GetParamFloat(const key[]);

//tokens

//ratelimit per minute; -1 = infinity
native AddToken(const token[], ratelimit = -1); 
native DeleteToken(const token[]);
native bool:ExistsToken(const token[]);
native ToggleRequiredToken(bool:toggle); //enable/disable the need for a token to access the API
native bool:GetRequiredToken();
native SetRateLimit(const token[], ratelimit); //limite per minute
native GetRateLimit(const token[]);