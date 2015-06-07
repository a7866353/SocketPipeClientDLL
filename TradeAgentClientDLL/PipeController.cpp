#include "stdafx.h"

#include "SocketConnector.h"
#include "PacketAnalyzer.h"
#include "PacketWriter.h"
#include "TradeAgentClientDLL.h"
#include <stdio.h>

static char* ipAddressString = "127.0.0.1";
static int port = 9000;

#define D_SEND_BUFFER_LENGTH 4096
#define D_RCV_BUFFER_LENGTH 4096
static char gRcvBuffer[D_RCV_BUFFER_LENGTH];
static int gRcvLength;
static SocketConnectionHandle gSocketHandle;

EXTERN_C
{
	static int gCount;
	TRADEAGENTCLIENTDLL_API int __stdcall InitSocket()
	{
		printf("InitConnection \n");
		gSocketHandle = SocketConnector_Create();
		SocketConnector_Connect(gSocketHandle, ipAddressString, port);

		PacketAnalyzerInit();

		return 0;
	}
	TRADEAGENTCLIENTDLL_API int __stdcall CloseSocket()
	{
		printf("CloseConnection \n");
		CloseConnection(&gSocketHandle);
		return 0;
	}

	TRADEAGENTCLIENTDLL_API int __stdcall GetPacket(PacketReaderHandle *handle)
	{
		Packet packet;
		int ret = 0;
		*handle = NULL;
		gRcvLength = D_RCV_BUFFER_LENGTH;
		ret = GetSocketRequest(gSocketHandle, gRcvBuffer, &gRcvLength);
		if (ret <= 0)
		{
			printf("GetType: not connected\r\n");
			return ret;
		}
		ret = PacketAnalyzerAddData(gRcvBuffer, gRcvLength, &packet);
		if (ret == 1)
		{
			// Get packet
			*handle = PacketReaderCreate(packet);

		}

		return(0);
	}

	TRADEAGENTCLIENTDLL_API int __stdcall SendPacket(PacketWriterHandle handle)
	{
		Packet packet;
		char *buffer;
		int length;
		int ret;
		PacketWriterGetPacket(handle, &packet);
		PacketAnalyzerSetHeader(&packet, &buffer, &length);
		ret = SendSocketResult(gSocketHandle, buffer, length);
		return 0;
	}
}