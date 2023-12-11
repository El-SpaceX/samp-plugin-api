#include "plugin.hpp"

bool Plugin::OnLoad() {
	//callbacks
	RegisterNative<&Script::n_RegisterHandle>("RegisterHandle");
	RegisterNative<&Script::n_DeleteHandle>("DeleteHandle");

	//server
	RegisterNative<&Script::n_StartServer>("StartServer");
	RegisterNative<&Script::n_StopServer>("StopServer");
	RegisterNative<&Script::n_IsServerRunning>("IsServerRunning");

	//content
	RegisterNative<&Script::n_SetContent>("SetContent");
	RegisterNative<&Script::n_SetContentHTML>("SetContentHTML");

	//params
	RegisterNative<&Script::n_GetNumParams>("GetNumParams");
	RegisterNative<&Script::n_HasParam>("HasParam");
	RegisterNative<&Script::n_GetParam>("GetParam");
	RegisterNative<&Script::n_GetParamInt>("GetParamInt");
	RegisterNative<&Script::n_GetParamFloat>("GetParamFloat");


	//token
	RegisterNative<&Script::n_AddToken>("AddToken");
	RegisterNative<&Script::n_DeleteToken>("DeleteToken");
	RegisterNative<&Script::n_ExistsToken>("ExistsToken");
	RegisterNative<&Script::n_ToggleRequiredToken>("ToggleRequiredToken");
	RegisterNative<&Script::n_GetRequiredToken>("GetRequiredToken");
	RegisterNative<&Script::n_SetRateLimit>("SetRateLimit"); //per minute
	RegisterNative<&Script::n_GetRateLimit>("GetRateLimit"); //per minute

	Log("plugin loaded.");
	return true;
}

bool Plugin::OnUnload() {
	APIServer::api.StopServer();
	Log("plugin unloaded.");
	return true;
}