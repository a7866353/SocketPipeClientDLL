#pragma once

typedef void* PacketReaderHandle;

PacketReaderHandle PacketReaderCreate(Packet packet);
int PacketReaderFree(PacketReaderHandle handle);

int RequestGetLong(PacketReaderHandle *handle, ULONG64 *output);
int RequestGetInt(PacketReaderHandle *handle, int *output);
int RequestGetShort(PacketReaderHandle *handle, short *output);
int RequestGetChar(PacketReaderHandle *handle, char *output);
int RequestGetDouble(PacketReaderHandle *handle, double *output);
int RequestGetString(PacketReaderHandle *handle, char* pStr, int length);
