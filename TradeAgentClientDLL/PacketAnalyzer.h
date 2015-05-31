#pragma once

struct Packet
{
	char* buffer;
	int length;
};


extern void PacketAnalyzerInit();
extern int PacketAnalyzerAddData(char* buffer, int length, Packet *packet);
