#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H

enum RequestType
{
	RequestType_None = 0,
	RequestType_Test,
	RequestType_SendOrder,
	RequestType_SendOrder_Result,
	RequestType_RateByTime,
	RequestType_RateByTime_Indicate,
	RequestType_SymbolNameList,
	RequestType_SymbolNameList_Result,
};

#define D_TIME_STRING_MAX (20)
typedef char TimeStr[D_TIME_STRING_MAX];

#define D_SYMBOL_NAME_MAX (24)
typedef char SymbolName[D_SYMBOL_NAME_MAX];

#ifdef TRADEAGENTCLIENTDLL_EXPORTS
#define TRADEAGENTCLIENTDLL_API __declspec(dllexport)
#else
#define TRADEAGENTCLIENTDLL_API __declspec(dllimport)
#endif

#endif // COMMON_TYPE_H