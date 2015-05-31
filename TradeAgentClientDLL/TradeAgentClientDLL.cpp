// TradeAgentClientDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "stdio.h"
#include "TradeAgentClientDLL.h"
#include "SocketConnector.h"

// ���ǵ���������һ��ʾ��
TRADEAGENTCLIENTDLL_API int nTradeAgentClientDLL=0;

// ���ǵ���������һ��ʾ����
TRADEAGENTCLIENTDLL_API int fnTradeAgentClientDLL(void)
{
	return 42;
}


#define D_SEND_BUFFER_LENGTH 4096
#define D_RCV_BUFFER_LENGTH 4096



static char* ipAddressString = "127.0.0.1";
static int port = 9000;
static SocketConnectionHandle gSocketHandle;

static char gRcvBuffer[D_RCV_BUFFER_LENGTH];
static int gRcvLength;

int SendResult(char *buffer, int length)
{
	SendSocketResult(gSocketHandle, buffer, length);
	return 0;
}
