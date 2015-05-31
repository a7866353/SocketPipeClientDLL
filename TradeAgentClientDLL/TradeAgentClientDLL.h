#pragma once

#include "Requests.h"
#include "Indications.h"

extern "C"
{
	TRADEAGENTCLIENTDLL_API int __stdcall InitSocket();
 	TRADEAGENTCLIENTDLL_API int __stdcall CloseSocket();
	TRADEAGENTCLIENTDLL_API int __stdcall GetType(RequestType *type);
}


