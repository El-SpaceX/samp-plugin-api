#include <a_samp>
#include <samp-web-api>

main() {}

WAPI_ROUTE:OnParam(const ip[], port)
{
	if(!WAPI_HasParam("int") || !WAPI_HasParam("float") || !WAPI_HasParam("str"))
	{
		WAPI_SetContent("Invalid params");
		return 500;
	}

	static response[256], str[32];
	WAPI_GetParam("str", str);
	format(response, sizeof response, "Int = %d | Float = %f | str = %s", WAPI_GetParamInt("int"), WAPI_GetParamFloat("float"), str);
	WAPI_SetContent(response);
	return 200;
}

WAPI_ROUTE:OnPathParams(const ip[], port)
{
	static response[256], str[32];
	WAPI_GetPathParam("str", str);
	format(response, sizeof response, "Int = %d | Float = %f | str = %s", WAPI_GetPathParamInt("int"), WAPI_GetPathParamFloat("float"), str);
	WAPI_SetContent(response);
	return 200;
}


public OnGameModeInit()
{
	WAPI_AddRoute(METHOD_GET, "/param", "OnParam");								//  http://localhost:8080/param?int=number&float=number&str=src
	WAPI_AddRoute(METHOD_GET, "/param_path/:int/:float/:str", "OnPathParams");	// 	http://localhost:8080/number/float/src
	WAPI_Run("localhost", 8080);
	return 1;
}


