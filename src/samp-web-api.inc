/*
@author: El-SpaceX
@github: https://github.com/El-SpaceX
*/

#if defined SAMP_WEBAPI_INCLUDED
    #endinput
#endif
#define SAMP_WEBAPI_INCLUDED

#define WAPI_ROUTE:%0(%1) \
		forward %0(%1); \
  		public %0(%1)

enum HTTP_METHOD
{
    METHOD_GET,
	METHOD_POST,
	METHOD_PUT,
	METHOD_PATCH,
	METHOD_DELETE
};


//manager web api
native bool:WAPI_AddRoute(HTTP_METHOD:method, const route[], const callback[]);
native bool:WAPI_Run(const host[], port);
native bool:WAPI_Stop();
native bool:WAPI_IsRunning();
native bool:WAPI_SetContent(const content[], const content_type[]="text/plain");

//headers
native bool:WAPI_HasHeader(const header[]);
native bool:WAPI_GetHeader(const header[], output[], size = sizeof output);
native WAPI_GetHeaderInt(const header[]);
native bool:WAPI_GetHeaderBool(const header[]) = WAPI_GetHeaderInt;
native Float:WAPI_GetHeaderFloat(const header[]);

//params
native bool:WAPI_HasParam(const param[]);
native bool:WAPI_GetParam(const param[], output[], size = sizeof output);
native WAPI_GetParamInt(const param[]);
native bool:WAPI_GetParamBool(const param[]) = WAPI_GetParamInt;
native Float:WAPI_GetParamFloat(const param[]);

//path-params
native bool:WAPI_HasPathParam(const param[]);
native bool:WAPI_GetPathParam(const param[], output[], size = sizeof output);
native WAPI_GetPathParamInt(const param[]);
native bool:WAPI_GetPathParamBool(const param[]) = WAPI_GetPathParamInt;
native Float:WAPI_GetPathParamFloat(const param[]);

//body
native WAPI_GetContentBody(output[], size = sizeof output);
native WAPI_GetBodySize();