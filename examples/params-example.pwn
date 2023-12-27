#include <a_samp>
#include <samp-plugin-api>

main() {}

API_CALLBACK OnParam(const ip[], port)
{
	if(!API_HasParam("int") || !API_HasParam("float") || !API_HasParam("str"))
	{
		API_SetContent("Invalid params");
		return 500;
	}

	static str[256];
	format(str, sizeof str, "Int = %d | Float = %f | str = %s", API_GetParamInt("int"), API_GetParamFloat("float"), API_GetParam("str"));
	API_SetContent(str);
	return 200;
}

API_CALLBACK OnPathParams(const ip[], port)
{
	static str[256];
	format(str, sizeof str, "Int = %d | Float = %f | str = %s", API_GetPathParamInt("int"), API_GetPathParamFloat("float"), API_GetPathParam("str"));
	API_SetContent(str);
	return 200;
}


public OnGameModeInit()
{
	API_AddGet("/param", "OnParam"); 							//  http://localhost:8080/param?int=number&float=number&str=src
	API_AddGet("/param_path/:int/:float/:str", "OnPathParams"); // 	http://localhost:8080/number/number/src
	API_Start("localhost", 8080);
	return 1;
}


