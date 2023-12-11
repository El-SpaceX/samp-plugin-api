#ifndef _PPLUGIN_H_
#define _PPLUGIN_H_

#include <samp-ptl/ptl.h>
#include "api.hpp"
#include "script.hpp"

class Plugin : public ptl::AbstractPlugin<Plugin, Script> {
public: 
	inline const char* Name() { return "api-plugin"; };
	bool OnLoad();
	bool OnUnload();
};

#endif