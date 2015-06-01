// TradeAgentClientDllTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "TradeAgentClientDLL.h"


#define D_RATEINFO_COUNT (3)

int _tmain(int argc, _TCHAR* argv[])
{
	PacketReaderHandle readHandle;
	PacketWriterHandle writeHandle;
	InitSocket();

	while (true)
	{
		GetPacket(&readHandle);
		if (readHandle != NULL)
		{
			writeHandle = PacketWriterCreate();
			PacketWriterSetByte(writeHandle, 0x01);
			PacketWriterSetInt(writeHandle, 0x11223344);
			PacketWriterSetString(writeHandle, "AABBCCDDEE");
			SendPacket(writeHandle);
			PacketWriterFree(writeHandle);

			PacketReaderFree(readHandle);
		}

		Sleep(1000);

	}

	getchar();
	return 0;
}

