#pragma once

typedef void* SocketConnectionHandle;
typedef void(*SocketConnectionReceiveCallback)(char* , int );

int InitConnection(char* ipAddress, int port, SocketConnectionHandle *handle);
int CloseConnection(SocketConnectionHandle *handle);
int GetSocketRequest(SocketConnectionHandle handle, char *buffer, int *length);
int SendSocketResult(SocketConnectionHandle handle, char *buffer, int length);

