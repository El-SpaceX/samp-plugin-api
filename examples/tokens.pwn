#include <a_samp>
#include <samp-plugin-api>

main() {}

API_CALLBACK OnBan(const ip[], const port)
{
	if(!API_HasParam("id")) 
		return 500;

	new id = API_GetParamInt("id");
	if(!IsPlayerConnected(id))
		return 501; //random codes

	Ban(id);
	SendClientMessage(id, -1, "Banned from API");
	return 200;
}



public OnGameModeInit()
{
	API_AddGet("/ban", "OnBan"); //http://localhost:8080/ban?id=id
	API_AddToken("hashi904909i9i9i40iIloveYou", 5); //max 5 requests per minute
	API_AddToken("hashi904909i9i9i40iIloveYou2", -1); //unlimited requests
	API_ToggleRequiredToken(true); //active token verify
	API_Start("localhost", 8080);
	return 1;
}


/*

header with token 
{
	"Authorization" : "token"
}
*/

