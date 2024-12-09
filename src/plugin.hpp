#pragma once

class Plugin : public ptl::AbstractPlugin<Plugin, Script> 
{
public: 
	inline const char* Name() { return "samp-web-api"; }
	int Version() { return PAWN_WEBAPI_VERSION; }
	bool OnLoad();
	bool OnUnload();
	static Plugin& Get() { return Instance(); }
private:
};
