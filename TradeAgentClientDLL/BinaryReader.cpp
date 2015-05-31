#include "stdafx.h"
#include "binaryReader.h"
#include <string.h>

void BinaryReaderInit(char *dataPth, int length, BinaryReaderControl *ctrl)
{
	ctrl->dataPtr = dataPth;
	ctrl->length = length;
	ctrl->index = 0;
}
int BinaryReaderGetLong(BinaryReaderControl *ctrl, ULONG64 *output)
{
	int len = 8;
	if (ctrl->index + len > ctrl->length)
		return -1;

	ULONG64* p = (ULONG64*)(ctrl->dataPtr + ctrl->index);

	int size = sizeof(ULONG64);
	*output = *p;
	ctrl->index += len;

	return 0;
}
int BinaryReaderGetInt(BinaryReaderControl *ctrl, int *output)
{
	int len = 4;
	if (ctrl->index + len > ctrl->length)
		return -1;

	int* p = (int*)(ctrl->dataPtr + ctrl->index);

	*output = *p;
	ctrl->index += len;

	return 0;
}
int BinaryReaderGetShort(BinaryReaderControl *ctrl, short *output)
{
	int len = 2;
	if (ctrl->index + len > ctrl->length)
		return -1;

	short* p = (short*)(ctrl->dataPtr + ctrl->index);

	*output = *p;
	ctrl->index += len;

	return 0;
}

int BinaryReaderGetChar(BinaryReaderControl *ctrl, char *output)
{
	int len = 1;
	if (ctrl->index + len > ctrl->length)
		return -1;

	char* p = (char*)(ctrl->dataPtr + ctrl->index);

	*output = *p;
	ctrl->index += len;

	return 0;
}

int BinaryReaderGetDouble(BinaryReaderControl *ctrl, double *output)
{
	int len = 8;
	if (ctrl->index + len > ctrl->length)
		return -1;

	double* p = (double*)(ctrl->dataPtr + ctrl->index);

	*output = *p;
	ctrl->index += len;

	return 0;
}

int BinaryReaderGetString(BinaryReaderControl *ctrl, char* pStr, int length)
{
	char* p = (char*)(ctrl->dataPtr + ctrl->index);
	int len = strnlen(p, length)+1;
	if (ctrl->index + len > ctrl->length)
		return -1;

	memcpy(pStr, p, len);
	ctrl->index += len;

	return 0;
}
