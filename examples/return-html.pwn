#include <a_samp>
#include <samp-plugin-api>

main() {}

API_CALLBACK OnHTML(const ip[], port)
{
	API_SetContentHTML("<html><button onclick=\"alert('Oh Yes')\">Click here</button></html>");
	return 200;
}

public OnGameModeInit()
{
	API_AddGet("/html", "OnHTML");
	API_Start("localhost", 8080);
	return 1;
}


