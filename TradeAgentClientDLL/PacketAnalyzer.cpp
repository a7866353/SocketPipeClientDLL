#include "stdafx.h"
#include "PacketAnalyzer.h"
#include "binaryReader.h"
#include "BinaryWriter.h"
#include <malloc.h>
#include <math.h>

static const char PACKET_START_FLAG = 0xAA;
typedef void(*DataAddFunc)();
enum ANALYZER_STATUS
{
	ANALYZER_STATUS_NONE,
	ANALYZER_STATUS_START_RECEIVE,
	ANALYZER_STATUS_RECEIVING,
};
struct PacketReceiveController
{
	bool isAvailable;
	char* buffer;
	int packetLength;
	int index;
	BinaryReaderControl readerCtrl;
};

struct PacketAnalyzController
{
	ANALYZER_STATUS status;
	char *buffer;
	int length;
	int index;
	DataAddFunc addFunc;
	PacketReceiveController rcvCtrl;
};

static PacketAnalyzController gCtrl;
static const char gPacketStartFlag[] = { 0xAA };


static void ReceiveData();

void  Add(char* buffer, int length)
{

}


static char ReadByte()
{
	return gCtrl.buffer[gCtrl.index];
}
static char* GetAddress()
{
	return &gCtrl.buffer[gCtrl.index];
}
static int RemainBytes()
{
	return (gCtrl.length - gCtrl.index);
}
static bool Next()
{
	if (gCtrl.index >= gCtrl.length)
		return false;
	else if (gCtrl.index == gCtrl.length - 1)
	{
		gCtrl.index++;
		return false;
	}
	
	gCtrl.index++;
	return true;
}
static bool IsReadEnd()
{
	if (gCtrl.index >= gCtrl.length)
		return true;
	else
		return false;
}

static void CheckPacketBegin()
{
	char ch;
	while (true)
	{
		ch = ReadByte();
		if (PACKET_START_FLAG == ch)
		{
			Next();
			gCtrl.status = ANALYZER_STATUS_RECEIVING;
			gCtrl.addFunc = ReceiveData;
			return;
		}

		if (Next() == false)
			return;
	}

}

static void ReceiveData()
{
	PacketReceiveController* ctrl = &gCtrl.rcvCtrl;
	int remain;
	int readCount;
	if (ctrl->isAvailable == false)
	{
		int length;
		int ret;
		BinaryReaderControl binCtrl;
		BinaryReaderInit(GetAddress(), RemainBytes(), &binCtrl);
		ret = BinaryReaderGetInt(&binCtrl, &ctrl->packetLength);

		gCtrl.index += 4;
		ctrl->index = 0;
		ctrl->buffer = (char *)malloc(ctrl->packetLength);
		ctrl->isAvailable = true;
	}
	remain = ctrl->packetLength - ctrl->index;
	readCount = min((remain), RemainBytes());
	memcpy(ctrl->buffer + ctrl->index, GetAddress(), readCount);
	ctrl->index += readCount;
	gCtrl.index += readCount;

	if (ctrl->index >= ctrl->packetLength)
	{
		gCtrl.status = ANALYZER_STATUS_NONE;
		gCtrl.addFunc = CheckPacketBegin;
		ctrl->isAvailable = false;
	}
		
}

void ModeRun()
{
	while (IsReadEnd() == false)
	{
		gCtrl.addFunc();
	}
}

//==================================================
void PacketAnalyzerInit()
{
	memset(&gCtrl, 0, sizeof(gCtrl));
	gCtrl.addFunc = CheckPacketBegin;
}

int PacketAnalyzerAddData(char* buffer, int length, Packet *packet)
{
	PacketReceiveController* rcvCtrl = &gCtrl.rcvCtrl;
	gCtrl.buffer = buffer;
	gCtrl.index = 0;
	gCtrl.length = length;

	ModeRun();
	if ((rcvCtrl->packetLength != 0) && (rcvCtrl->index == rcvCtrl->packetLength) )
	{
		packet->buffer = rcvCtrl->buffer;
		packet->length = rcvCtrl->packetLength;
		return 1;
	}
	return 0;
}

int PacketAnalyzerSetHeader(Packet *packet, char** buffer, int *length )
{
	BinaryWriterControl ctrl;

	BinaryWriter_Init(&ctrl, packet->buffer, packet->length);
	BinaryWriter_SetByte(&ctrl, PACKET_START_FLAG);
	BinaryWriter_SetInt(&ctrl, packet->length-5);
	*buffer = packet->buffer;
	*length = packet->length;
	
	return 0;
}