#pragma once
#include "CommonType.h"
#include "PacketAnalyzer.h"

EXTERN_C
{
	typedef void* PacketReaderHandle;

	PacketReaderHandle PacketReaderCreate(Packet packet);

	TRADEAGENTCLIENTDLL_API int __stdcall PacketReaderFree(PacketReaderHandle handle);

	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetLong(PacketReaderHandle handle, ULONG64 *output);
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetInt(PacketReaderHandle handle, int *output);
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetShort(PacketReaderHandle handle, short *output);
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetChar(PacketReaderHandle handle, char *output);
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetDouble(PacketReaderHandle handle, double *output);
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetString(PacketReaderHandle handle, char* pStr, int length);
}