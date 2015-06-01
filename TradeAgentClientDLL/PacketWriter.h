#pragma once
#include "CommonType.h"
#include "PacketAnalyzer.h"

EXTERN_C
{
	typedef void* PacketWriterHandle;

	void PacketWriterGetPacket(PacketWriterHandle handle, Packet *packet);

	TRADEAGENTCLIENTDLL_API PacketWriterHandle __stdcall PacketWriterCreate();
	TRADEAGENTCLIENTDLL_API void __stdcall PacketWriterFree(PacketWriterHandle handle);

	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetByte(PacketWriterHandle handle, char data);
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetShort(PacketWriterHandle handle, short data);
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetInt(PacketWriterHandle handle, int data);
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetLong(PacketWriterHandle handle, ULONG64 data);
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetDouble(PacketWriterHandle handle, double data);
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetString(PacketWriterHandle handle, char *data);

}
