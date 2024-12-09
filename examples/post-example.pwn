#include <a_samp>
#include <samp-web-api>

main() {}

WAPI_ROUTE:OnCreateUser(const ip[], port)
{
	static body[256];
	WAPI_GetContentBody(body);
	printf("User %s created!", body);
	return 200;
}

public OnGameModeInit()
{
	WAPI_AddRoute(METHOD_POST, "/CreateUser", "OnCreateUser");
	WAPI_Run("localhost", 5000);
	return 1;
}