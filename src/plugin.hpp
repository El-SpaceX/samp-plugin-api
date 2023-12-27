#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <samp-ptl/ptl.h>
#include "script.hpp"

class Plugin : public ptl::AbstractPlugin<Plugin, Script> 
{
public: 
	inline const char* Name() { return "samp-plugin-api"; }
	bool OnLoad();
	bool OnUnload();
	static Plugin& Get() { return Instance(); }
private:
};

#endif