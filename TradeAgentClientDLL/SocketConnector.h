#pragma once

typedef void* SocketConnectionHandle;
typedef void(*SocketConnectionReceiveCallback)(char* , int );

SocketConnectionHandle SocketConnector_Create();
int SocketConnector_Connect(SocketConnectionHandle handle, char* ipAddress, int port);
int CloseConnection(SocketConnectionHandle *handle);
int GetSocketRequest(SocketConnectionHandle handle, char *buffer, int *length);
int SendSocketResult(SocketConnectionHandle handle, char *buffer, int length);

