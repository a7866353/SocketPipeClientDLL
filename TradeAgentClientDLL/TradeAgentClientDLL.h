#pragma once
#include "PacketReader.h"
#include "PacketWriter.h"
extern "C"
{
	TRADEAGENTCLIENTDLL_API int __stdcall InitSocket();
 	TRADEAGENTCLIENTDLL_API int __stdcall CloseSocket();
	TRADEAGENTCLIENTDLL_API int __stdcall GetPacket(PacketReaderHandle *handle);
	TRADEAGENTCLIENTDLL_API int __stdcall SendPacket(PacketWriterHandle handle);


}


