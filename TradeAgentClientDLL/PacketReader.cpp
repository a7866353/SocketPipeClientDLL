#include "stdafx.h"
#include "Common.h"
#include "PacketReader.h"
#include "PacketAnalyzer.h"
#include "binaryReader.h"
#include <malloc.h>

struct PacketReader
{
	char *buffer;
	int length;
	BinaryReaderControl binCtrl;
};

EXTERN_C
{
	PacketReaderHandle PacketReaderCreate(Packet packet)
	{
		PacketReader* reader = (PacketReader *)malloc(sizeof(PacketReader));
		memset(reader, 0, sizeof(PacketReader));
		reader->buffer = packet.buffer;
		reader->length = packet.length;
		BinaryReaderInit(reader->buffer, reader->length, &reader->binCtrl);
		return (PacketReaderHandle)reader;
	}

	TRADEAGENTCLIENTDLL_API int __stdcall PacketReaderFree(PacketReaderHandle handle)
	{
		PacketReader *reader = (PacketReader *)handle;
		free(reader->buffer);
		free(reader);
		return 0;
	}

	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetLong(PacketReaderHandle *handle, ULONG64 *output)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetLong(&ctrl->binCtrl, output);
	}

	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetInt(PacketReaderHandle *handle, int *output)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetInt(&ctrl->binCtrl, output);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetShort(PacketReaderHandle *handle, short *output)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetShort(&ctrl->binCtrl, output);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetChar(PacketReaderHandle *handle, char *output)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetChar(&ctrl->binCtrl, output);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetDouble(PacketReaderHandle *handle, double *output)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetDouble(&ctrl->binCtrl, output);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall RequestGetString(PacketReaderHandle *handle, char* pStr, int length)
	{
		PacketReader *ctrl = (PacketReader *)handle;
		return BinaryReaderGetString(&ctrl->binCtrl, pStr, length);
	}

}