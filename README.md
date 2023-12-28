# samp-plugin-api


I created this plugin as a study project. In summary, it allows you to create an API within samp-server.exe, enabling you to retrieve values and execute instructions through requests.

The plugin also includes a security system with rate limiting using tokens, which can be activated or deactivated at your discretion. This ensures that requests are only processed if they are verified with the token. See some example [here](https://github.com/El-SpaceX/samp-plugin-api/tree/main/examples).

### Example

```c
#include <a_samp>
#include <samp-plugin-api>

API_CALLBACK OnSendAll(const ip[], const port)
{
    SendClientMessageToAll(-1, "ping!");
    return 200;
}

API_CALLBACK OnGetName(const ip[], const port)
{
    if(!API_HasPathParam("id"))
    {
        SetContent("Use: http://localhost:8080/GetName/:id");
        return 500;
    }

    new id = API_GetPathParamInt("id");
    
    //cellmin == invalid number
    if(id == cellmin)
    {
        SetContent("Use: http://localhost:8080/GetName/:id");
        return 500;
    }

    if(id < MAX_PLAYERS || id > 0)
    {
        SetContent("Id invalid.");
        return 500;
    }

    new pName[MAX_PLAYER_NAME + 1];
    GetPlayerName(id, pName, sizeof pName);
    SetContent(pName);
    return 200;
}

public OnGameModeInit()
{
    API_AddPost("/SendAll", "OnSendAll");
    API_AddGet("/GetName/:id", "OnGetName");

    API_Start("localhost", 8080); //Inicia a API no localhost na porta 8080. (http://localhost:8080/)
    return 1;
}

```
