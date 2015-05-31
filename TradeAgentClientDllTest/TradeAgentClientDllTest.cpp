// TradeAgentClientDllTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "TradeAgentClientDLL.h"


#define D_RATEINFO_COUNT (3)
static RateInfo gRateInfoArr[D_RATEINFO_COUNT];

int _tmain(int argc, _TCHAR* argv[])
{
	RequestType type;
	RateInfo *pInfo;
	InitSocket();

	while (true)
	{
		GetType(&type);
		switch (type)
		{
			case RequestType_RateByTime:
			{
				if (true)
				{
					pInfo = &gRateInfoArr[0];
					memcpy(pInfo->time, "2014.01.12 01:20:01", sizeof(TimeStr));
					pInfo->high = 120.0;
					pInfo->low = 100.2;
					pInfo->open = 110.1;
					pInfo->close = 111.3;

					pInfo = &gRateInfoArr[1];
					memcpy(pInfo->time, "2014.01.12 01:21:01", sizeof(TimeStr));
					pInfo->high = 120.0;
					pInfo->low = 100.2;
					pInfo->open = 110.1;
					pInfo->close = 111.3;

					pInfo = &gRateInfoArr[2];
					memcpy(pInfo->time, "2014.01.12 01:22:01", sizeof(TimeStr));
					pInfo->high = 120.0;
					pInfo->low = 100.2;
					pInfo->open = 110.1;
					pInfo->close = 111.3;
					pInfo->isEnd = true;
					SendRateByTimeIndicate(gRateInfoArr, D_RATEINFO_COUNT, 1);
				}
				else
				{
					SendRateByTimeIndicate(gRateInfoArr, 0, 1);
				}
				break;
			}
			case RequestType_SendOrder:
			{
				SendOrderRequest req;
				GetSendOrderReq(&req);
				SendSendOrderResult();
				break;
			}
			case RequestType_SymbolNameList:
			{
				SymbolNameListResult symReq;
				memcpy(symReq.symbolNameArr[0], "Test01", sizeof("Test01"));
				memcpy(symReq.symbolNameArr[1], "Test02", sizeof("Test02"));
				SendSymbolNameListResult(&symReq, 2);
				break;
			}
		}


		Sleep(1000);

	}

	getchar();
	return 0;
}

