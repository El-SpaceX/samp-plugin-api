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
    RegisterHandle("/hi/", "OnHelloWorld"); 		// LINK: http://localhost:8080/hi/
    RegisterHandle("/hello/", "OnSendMessage"); 	// LINK: http://localhost:8080/hello/
    StartServer("localhost", 8080);		 			// LINK: http://localhost:8080/
    AddToken("token12345", -1); 					// this token does not contain rate limit
    AddToken("token54321", 20); 					// this token contains rate limit of 50 requests per minute
    ToggleRequiredToken(true);                      // activates the need for a token to make requests
	
    /* To make the request with the token we must place it in the headers like this
    {
        "Authorization" : "you-token"
    }
    */
	
    return 1;
}
```