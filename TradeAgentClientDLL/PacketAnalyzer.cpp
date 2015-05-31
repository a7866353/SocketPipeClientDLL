#include "stdafx.h"
#include "PacketAnalyzer.h"
#include "binaryReader.h"
#include <malloc.h>
#include <math.h>

#define PACKET_START_FLAG (0x55)
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
	char index;
	DataAddFunc addFunc;
	PacketReceiveController rcvCtrl;
};

static PacketAnalyzController gCtrl;
static const char gPacketStartFlag[] = { 0xAA };

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
	while (true)
	{
		if (PACKET_START_FLAG == ReadByte())
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

		ctrl->index = 0;
		ctrl->buffer = (char *)malloc(ctrl->packetLength);
		ctrl->isAvailable = true;
	}
	remain = ctrl->packetLength - ctrl->index;
	readCount = min((remain), RemainBytes());
	memcpy(ctrl->buffer + ctrl->index, GetAddress(), readCount);
	ctrl->index += readCount;

	if (ctrl->index >= ctrl->packetLength)
	{
		gCtrl.status = ANALYZER_STATUS_NONE;
		gCtrl.addFunc = CheckPacketBegin;
	}
		
}

void ModeRun()
{
	while (IsReadEnd == false)
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
	if (rcvCtrl->index == rcvCtrl->packetLength)
	{
		packet->buffer = rcvCtrl->buffer;
		packet->length = rcvCtrl->packetLength;
		return 1;
	}
	return 0;
}