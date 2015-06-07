// TradeAgentClientDllTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "TradeAgentClientDLL.h"


#define D_RATEINFO_COUNT (3)
enum RequestType
{
	None = 0,
	TestRequest,
	SendOrderRequest,
	SendOrderResult,
	RateDataRequest,
	RateDataIndicate,
	SymbolNameListRequest,
	SymbolNameListResult,
};
static char valueStr[4096 * 1000];

int _tmain(int argc, _TCHAR* argv[])
{
	PacketReaderHandle readHandle;
	PacketWriterHandle writeHandle;
	InitSocket();

	while (true)
	{
		GetPacket(&readHandle);
		if (readHandle == NULL)
		{
			Sleep(1);
			continue;
		}

		int type;
		int valueInt;
		short valueShort;
		char valueChar;
		double valueDouble;

		RequestGetInt(readHandle, &type);
		writeHandle = PacketWriterCreate();
		switch (type)
		{
			case TestRequest:
				PacketWriterSetInt(writeHandle, type);

				RequestGetDouble(readHandle, &valueDouble);
				PacketWriterSetDouble(writeHandle, valueDouble);

				RequestGetInt(readHandle, &valueInt);
				PacketWriterSetInt(writeHandle, valueInt);

				RequestGetString(readHandle, valueStr, sizeof(valueStr));
				PacketWriterSetString(writeHandle, valueStr);

				RequestGetString(readHandle, valueStr, sizeof(valueStr));
				PacketWriterSetString(writeHandle, valueStr);
				break;
			default:
				break;
		}
		SendPacket(writeHandle);
		PacketWriterFree(writeHandle);
		PacketReaderFree(readHandle);
	}

	getchar();
	return 0;
}

