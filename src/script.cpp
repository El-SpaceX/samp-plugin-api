#include "script.hpp"


using namespace APIServer;

// --------- server manager ---------
cell Script::n_RegisterHandle(const std::string pattern, const std::string callback) {
    std::string callback_name = callback;

    PublicPtr c = MakePublic(callback_name, false);
    if(!c->Exists())
        return 0;

    if(!pattern.empty()) {
        api.AddHandler(pattern, c);
    }
    else 
    {
        Log("Callback \"%s\" not found", callback.c_str());
    }
    return 1;
}

cell Script::n_DeleteHandle(const std::string pattern) {
    api.RemoveHandler(pattern);
    return 1;
}

cell Script::n_StartServer(std::string ip, int port) {
    if (api.IsAPIRunning())
        return 0;

    Log("Starting api..");
    api.StartServer(ip, port);
    return 1;
}

cell Script::n_StopServer() {

    if (!api.IsAPIRunning())
        return 0;

    Log("Closing api..");
    api.StopServer();
    Log("API closed.");
    return 1;
}

cell Script::n_IsServerRunning() {
    return static_cast<cell>(api.IsAPIRunning());
}


// --------- response content ---------
cell Script::n_SetContent(std::string content) {
    if (!api.IsAPIRunning() || !api.GetCurrentResponseTemp())
        return 0;

    api.GetCurrentResponseTemp()->set_content(content, "text/plain");
    return 1;
}

cell Script::n_SetContentHTML(std::string html) {
    if (!api.IsAPIRunning() || !api.GetCurrentResponseTemp())
        return 0;

    api.GetCurrentResponseTemp()->set_content(html, "text/html");
    return 1;
}


// --------- request params ---------
cell Script::n_HasParam(std::string key) {
    if (!api.GetCurrentRequestTemp())
        return 0;

    return api.GetCurrentRequestTemp()->has_param(key);
}


cell Script::n_GetParam(std::string key, cell* output, int size) {
    if (!api.GetCurrentRequestTemp()) {
        SetString(output, "(null)", size);
        return 0;
    }

    
    if(!api.GetCurrentRequestTemp()->has_param(key)) {
        SetString(output, "(null)", size);
        return 0;
    }


    SetString(output, api.GetCurrentRequestTemp()->get_param_value(key), size);
    return 0;
}

cell Script::n_GetParamInt(std::string key) {
    if (!api.GetCurrentRequestTemp()) 
        return 0;

      
    if (api.GetCurrentRequestTemp()->has_param(key)) {
        int value;
        
        try {
            value = std::stoi(api.GetCurrentRequestTemp()->get_param_value(key));
            return value;
        }
        catch (...) {
            return std::numeric_limits<int>::min();;
        }

    }
    return std::numeric_limits<int>::min();;
}

cell Script::n_GetParamFloat(std::string key) {
    if (!api.GetCurrentRequestTemp())
        return 0;


    float value;
    if (api.GetCurrentRequestTemp()->has_param(key)) {

        try {
            value = std::stof(api.GetCurrentRequestTemp()->get_param_value(key));
            return amx_ftoc(value);
        }
        catch (...) {
            value = std::numeric_limits<float>::min();
            return amx_ftoc(value);
        }

    }
    value = std::numeric_limits<float>::min();
    return amx_ftoc(value);
}

cell Script::n_GetNumParams() {
    if (!api.GetCurrentRequestTemp())
        return 0;

    return api.GetCurrentRequestTemp()->params.size();
}


cell Script::n_AddToken(Token token, int ratelimit) {

    // ratelimit < 0 = inifinity 
    api.AddToken(token, ratelimit < 0 ? -1 : ratelimit);
    return 1;
}

cell Script::n_SetRateLimit(Token token, int ratelimit) {
    api.SetRateLimit(token, ratelimit);
    return 1;
}

cell Script::n_GetRateLimit(Token token) {
    return api.GetRateLimit(token);
}

cell Script::n_DeleteToken(Token token) {
    api.RemoveToken(token);
    return 1;
}

cell Script::n_ExistsToken(Token token) {
    return api.ExistsToken(token);
}

cell Script::n_ToggleRequiredToken(int toggle) {
    api.ToggleTokenRequired(static_cast<bool>(toggle));
    return 1;
}

cell Script::n_GetRequiredToken() {
    return api.GetTokenRequired();
}
