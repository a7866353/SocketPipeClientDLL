#include "Common.h"
#include "PacketReader.h"
#include "PacketAnalyzer.h"
#include "binaryReader.h"
#include <malloc.h>

#define BUFFER_LENGTH_MAX (4096)

struct PacketReader
{
	char *buffer;
	int length;
	BinaryReaderControl binCtrl;
};

PacketReaderHandle PacketReaderCreate(Packet packet)
{
	PacketReader* reader = (PacketReader *)malloc(sizeof(PacketReader));
	memset(reader, 0, sizeof(PacketReader));
	reader->buffer = packet.buffer;
	reader->length = packet.length;
	BinaryReaderInit(reader->buffer, reader->length, &reader->binCtrl);
	return (PacketReaderHandle)reader;
}

int PacketReaderFree(PacketReaderHandle handle)
{
	PacketReader *reader = (PacketReader *)handle;
	free(reader->buffer);
	free(reader);
}

int RequestGetLong(PacketReaderHandle *handle, ULONG64 *output)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetLong(&ctrl->binCtrl, output);
}

int RequestGetInt(PacketReaderHandle *handle, int *output)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetInt(&ctrl->binCtrl, output);
}
int RequestGetShort(PacketReaderHandle *handle, short *output)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetShort(&ctrl->binCtrl, output);
}
int RequestGetChar(PacketReaderHandle *handle, char *output)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetChar(&ctrl->binCtrl, output);
}
int RequestGetDouble(PacketReaderHandle *handle, double *output)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetDouble(&ctrl->binCtrl, output);
}
int RequestGetString(PacketReaderHandle *handle, char* pStr, int length)
{
	PacketReader *ctrl = (PacketReader *)handle;
	return BinaryReaderGetString(&ctrl->binCtrl, pStr, length);
}

