#include <a_samp>
#include <samp-web-api>

main() {}

WAPI_ROUTE:OnHTML(const ip[], port)
{
	WAPI_SetContent("<html><button onclick=\"alert('Clicked')\">Click here</button></html>", "text/html");
	return 200;
}

public OnGameModeInit()
{
	WAPI_AddRoute(METHOD_GET, "/html", "OnHTML");
	WAPI_Run("localhost", 5000);
	return 1;
}


