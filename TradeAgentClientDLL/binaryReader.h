#ifndef BINARY_RADER_H
#define BINARY_RADER_H

struct BinaryReaderControl
{
	char *dataPtr;
	int length;
	int index;
	bool isBigEndian;
};

extern void BinaryReaderInit(char *dataPth, int length, BinaryReaderControl *ctrl);
extern int BinaryReaderGetLong(BinaryReaderControl *ctrl, ULONG64 *output);
extern int BinaryReaderGetInt(BinaryReaderControl *ctrl, int *output);
extern int BinaryReaderGetShort(BinaryReaderControl *ctrl, short *output);
extern int BinaryReaderGetChar(BinaryReaderControl *ctrl, char *output);
extern int BinaryReaderGetDouble(BinaryReaderControl *ctrl, double *output);
extern int BinaryReaderGetString(BinaryReaderControl *ctrl, char* pStr, int length);

#endif