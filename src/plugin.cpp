#include "main.hpp"

bool Plugin::OnLoad() 
{

	RegisterNative<&Script::WAPI_Run>("WAPI_Run");
	RegisterNative<&Script::WAPI_Stop>("WAPI_Stop");
	RegisterNative<&Script::WAPI_IsRunning>("WAPI_IsRunning");
	RegisterNative<&Script::WAPI_AddRoute>("WAPI_AddRoute");
	RegisterNative<&Script::WAPI_SetContent>("WAPI_SetContent");

	//header
	RegisterNative<&Script::WAPI_HasHeader>("WAPI_HasHeader");
	RegisterNative<&Script::WAPI_GetHeader>("WAPI_GetHeader");
	RegisterNative<&Script::WAPI_GetHeaderInt>("WAPI_GetHeaderInt");
	RegisterNative<&Script::WAPI_GetHeaderFloat>("WAPI_GetHeaderFloat");

	//params
	RegisterNative<&Script::WAPI_HasParam>("WAPI_HasParam");
	RegisterNative<&Script::WAPI_GetParam>("WAPI_GetParam");
	RegisterNative<&Script::WAPI_GetParamInt>("WAPI_GetParamInt");
	RegisterNative<&Script::WAPI_GetParamFloat>("WAPI_GetParamFloat");

	//path-params
	RegisterNative<&Script::WAPI_HasPathParam>("WAPI_HasPathParam");
	RegisterNative<&Script::WAPI_GetPathParam>("WAPI_GetPathParam");
	RegisterNative<&Script::WAPI_GetPathParamInt>("WAPI_GetPathParamInt");
	RegisterNative<&Script::WAPI_GetPathParamFloat>("WAPI_GetPathParamFloat");

	//body
	RegisterNative<&Script::WAPI_GetContentBody>("WAPI_GetContentBody");
	RegisterNative<&Script::WAPI_GetBodySize>("WAPI_GetBodySize");

	Log("\n\n\
	|- %s (%s)\n\
	|- Author: El-Spacex\n\
	|- Compiled: %s\
	\n\n", Name(), VersionAsString().c_str(), __DATE__);
	return true;
}

bool Plugin::OnUnload() 
{
	Log("plugin unloaded.");
	return true;
}