#pragma once

struct Packet
{
	char* buffer;
	int length;
};

#define PACKET_HEADER_SIZE (1+4)

extern void PacketAnalyzerInit();
extern int PacketAnalyzerAddData(char* buffer, int length, Packet *packet);
extern int PacketAnalyzerSetHeader(Packet *packet, char** buffer, int *length);