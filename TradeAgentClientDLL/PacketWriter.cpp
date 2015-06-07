#include "stdafx.h"
#include "PacketWriter.h"
#include "BinaryWriter.h"
#include <malloc.h>

#define PACKET_LENGTH (4096*1024+PACKET_HEADER_SIZE)

struct PacketWriterController
{
	BinaryWriterControl writerCtrl;
	char *buffer;
	int length;
};

EXTERN_C
{
	TRADEAGENTCLIENTDLL_API PacketWriterHandle __stdcall PacketWriterCreate()
	{
		PacketWriterController *ctrl = (PacketWriterController *)malloc(sizeof(PacketWriterController));
		ctrl->buffer = (char *)malloc(PACKET_LENGTH);
		ctrl->length = PACKET_LENGTH;
		BinaryWriter_Init(&ctrl->writerCtrl, ctrl->buffer, ctrl->length);
		BinaryWriter_Skip(&ctrl->writerCtrl, PACKET_HEADER_SIZE);

		return (PacketWriterHandle)ctrl;
	}

	TRADEAGENTCLIENTDLL_API void __stdcall PacketWriterFree(PacketWriterHandle handle)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		free(ctrl->buffer);
		free(ctrl);
	}
	
	void PacketWriterGetPacket(PacketWriterHandle handle, Packet *packet)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		packet->buffer = ctrl->buffer;
		packet->length = ctrl->writerCtrl.index;
	}

	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetByte(PacketWriterHandle handle, char data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetByte(&ctrl->writerCtrl, data);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetShort(PacketWriterHandle handle, short data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetShort(&ctrl->writerCtrl, data);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetInt(PacketWriterHandle handle, int data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetInt(&ctrl->writerCtrl, data);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetLong(PacketWriterHandle handle, ULONG64 data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetLong(&ctrl->writerCtrl, data);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetDouble(PacketWriterHandle handle, double data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetDouble(&ctrl->writerCtrl, data);
	}
	TRADEAGENTCLIENTDLL_API int __stdcall PacketWriterSetString(PacketWriterHandle handle, char *data)
	{
		PacketWriterController *ctrl = (PacketWriterController *)handle;
		return BinaryWriter_SetString(&ctrl->writerCtrl, data);
	}
}
