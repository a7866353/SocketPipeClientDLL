#include "stdafx.h"
#include <stdio.h>
#include <malloc.h>
#include <winsock2.h>                //Socket的函数调用　
#pragma comment (lib, "ws2_32")      //C语言引用其他类库时，除了.h文件外，还要加入对应的lib文件

#include "SocketConnector.h"

static char* gIPAddress = "127.0.0.1";
static int gPort = 9000;

static const int RCV_DATA_LENGTH_MAX = 1024 * 1024;
static char gRcvBuffer[RCV_DATA_LENGTH_MAX];
enum SOCKET_CONNECTION_STATUS
{
	SOCKET_CONNECTION_STATUS_DISCONNECTED,
	SOCKET_CONNECTION_STATUS_CONNECTED,
};
struct SocketConnection
{

	SOCKET connection;
	sockaddr_in address;
	SocketConnectionReceiveCallback rcvCallback;
	SOCKET_CONNECTION_STATUS status;
};

int getReadDataStatus(SOCKET s)
{
	fd_set fdRead;

	FD_ZERO(&fdRead);
	FD_SET(s, &fdRead);

	TIMEVAL tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	select(0, &fdRead, NULL, NULL, &tv);

	if (FD_ISSET(s, &fdRead))
	{
		return 0;
	}
	else
	{
		return -1;
	}

}

// =====================================================================
SocketConnectionHandle SocketConnector_Create()
{
	SocketConnection *h = (SocketConnection *)malloc(sizeof(SocketConnection));
	if (h == NULL)
	{
		return NULL;
	}
	memset(h, 0, sizeof(SocketConnection));
	h->status = SOCKET_CONNECTION_STATUS_DISCONNECTED;
	return h;
}

int SocketConnector_Connect(SocketConnectionHandle handle, char* ipAddress, int port)
{
	int ret;
	SocketConnection *h = (SocketConnection *)handle;
	memset(h, 0, sizeof(SocketConnection));

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	h->connection = s;

	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);
	sockaddr.sin_port = htons(port);
	h->address = sockaddr;

	ret = connect(s, (SOCKADDR *)&sockaddr, sizeof(sockaddr));
	if (ret == 0)
	{
		h->status = SOCKET_CONNECTION_STATUS_CONNECTED;
	}
	return ret;

}

int CloseConnection(SocketConnectionHandle *handle)
{
	SocketConnection *h = (SocketConnection *)handle;
	closesocket(h->connection); // 关闭监听socket

	WSACleanup(); //卸载

	free(h);
	return 0;
}


/*************************************************
*
* length(in/out): in - buffer max length. out - data length
* return:
*
**************************************************/
int GetSocketRequest(SocketConnectionHandle handle, char *buffer, int *length)
{
	SocketConnection *h = (SocketConnection *)handle;
	if (h->status == SOCKET_CONNECTION_STATUS_CONNECTED)
	{
		// data is received.
		int rcvCount = recv(h->connection, buffer, *length, NULL);
		if (rcvCount < 0)
		{
			h->status = SOCKET_CONNECTION_STATUS_DISCONNECTED;
			rcvCount = 0;
		}
		*length = rcvCount;
	}
	else
	{
		int ret;
		ret = connect(h->connection, (SOCKADDR *)&h->address, sizeof(sockaddr));
		if (ret == 0)
		{
			h->status = SOCKET_CONNECTION_STATUS_CONNECTED;
		}
		*length = 0;
	}
	return *length;
}

int SendSocketResult(SocketConnectionHandle handle, char *buffer, int length)
{
	SocketConnection *h = (SocketConnection *)handle;
	int sendCount = 0;
	if (h->status == SOCKET_CONNECTION_STATUS_CONNECTED)
	{		
		// send data
		sendCount = send(h->connection, buffer, length, NULL);
	}
	return sendCount;
}



