#include "plugin.hpp"

bool Plugin::OnLoad() 
{
	//callbacks
	RegisterNative<&Script::n_AddGet>("API_AddGet");
	RegisterNative<&Script::n_Start>("API_Start");
	RegisterNative<&Script::n_Stop>("API_Stop");
	RegisterNative<&Script::n_IsRunning>("API_IsRunning");


	//response manager
	RegisterNative<&Script::n_SetContent>("API_SetContent");
	RegisterNative<&Script::n_SetContentHTML>("API_SetContentHTML");


	//token
	RegisterNative<&Script::n_TokenExists>("API_TokenExists");
	RegisterNative<&Script::n_AddToken>("API_AddToken");
	RegisterNative<&Script::n_RemoveToken>("API_RemoveToken");
	RegisterNative<&Script::n_GetRateLimit>("API_GetRateLimit");
	RegisterNative<&Script::n_SetRateLimit>("API_SetRateLimit");
	RegisterNative<&Script::n_ToggleTokenRequired>("API_ToggleRequiredToken");
	RegisterNative<&Script::n_IsRequiredToken>("API_IsRequiredToken");

	//params
	RegisterNative<&Script::n_HasParam>("API_HasParam");
	RegisterNative<&Script::n_GetParam>("API_GetParamEx");
	RegisterNative<&Script::n_GetParamInt>("API_GetParamInt");
	RegisterNative<&Script::n_GetParamFloat>("API_GetParamFloat");
	RegisterNative<&Script::n_GetParamBool>("API_GetParamBool");

	//path params
	RegisterNative<&Script::n_HasPathParam>("API_HasPathParam");
	RegisterNative<&Script::n_GetPathParam>("API_GetPathParamEx");
	RegisterNative<&Script::n_GetPathParamInt>("API_GetPathParamInt");
	RegisterNative<&Script::n_GetPathParamFloat>("API_GetPathParamFloat");
	RegisterNative<&Script::n_GetPathParamBool>("API_GetPathParamBool");

	Log("plugin loaded.");
	return true;
}

bool Plugin::OnUnload() 
{
	Log("plugin unloaded.");
	return true;
}