#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include "stdafx.h"

struct BinaryWriterControl
{
	char *dataPtr;
	int maxLength;
	int index;
	bool isBigEndian;
};

extern void BinaryWriter_Init(BinaryWriterControl *ctrl, char *buffer, int size);
int BinaryWriter_Skip(BinaryWriterControl *ctrl, int pos);
extern int BinaryWriter_SetByte(BinaryWriterControl *ctrl, char data);
extern int BinaryWriter_SetShort(BinaryWriterControl *ctrl, short data);
extern int BinaryWriter_SetInt(BinaryWriterControl *ctrl, int data);
extern int BinaryWriter_SetLong(BinaryWriterControl *ctrl, ULONG64 data);
extern int BinaryWriter_SetDouble(BinaryWriterControl *ctrl, double data);
extern int BinaryWriter_SetString(BinaryWriterControl *ctrl, char *data);

#endif