# samp-plugin-api

This plugin allows you to run an API on samp-server, being able to manipulate what it will respond to

NOTE: I'm still studying C++, probably many things could be improved in this code (some changes that should sometimes be mandatory)


### Example

```c
#include <a_samp>
#include <samp-plugin-api>


main() {}

forward OnHelloWorld(const ip[], port);
public  OnHelloWorld(const ip[], port) {
    SetContent("Hello World");
    //200 = OK
    return 200;
}

forward OnSendMessage(const ip[], port);
public  OnSendMessage(const ip[], port) {
    if(!HasParam("playerid") || !HasParam("message") ) {
        SetContent("Use: http://localhost:8080/hello/?playerid=id&message=msg");
        return 400;
    }




    static message[128], id;
    id = GetParamInt("playerid");
    
    if(id == cellmin)
    {
        //no number
        SetContent("Use: http://localhost:8080/hello/?playerid=id&message=msg");
        return 400;
    }
    
    GetParam("message", message, sizeof message);
	printf("ID = %d | message = %s", id, message);
    SendClientMessage(id, -1, message);

    SetContent("OK :D");
    //200 = OK
    return 200;
}


public OnGameModeInit()
{
    RegisterHandle("/hi/", "OnHelloWorld"); // http://localhost:8080/hi/
    RegisterHandle("/hello/", "OnSendMessage"); // http://localhost:8080/hello/
    StartServer("localhost", 8080); // http://localhost:8080/
    return 1;
}

```