#include "stdafx.h"
#include "BinaryWriter.h"
#include <string.h>

void BinaryWriter_Init(BinaryWriterControl *ctrl, char *buffer, int size)
{
	ctrl->dataPtr = buffer;
	ctrl->index = 0;
	ctrl->maxLength = size;
}

int BinaryWriter_Skip(BinaryWriterControl *ctrl, int pos)
{
	if (ctrl->index + pos > ctrl->maxLength)
		return -1;

	ctrl->index += pos;
	return 0;
}

int BinaryWriter_SetByte(BinaryWriterControl *ctrl, char data)
{
	int len = 1;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	char *p = (char *)(ctrl->dataPtr + ctrl->index);
	*p = data;
	ctrl->index += len;
	
	return 0;
}

int BinaryWriter_SetShort(BinaryWriterControl *ctrl, short data)
{
	int len = 2;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	short *p = (short *)(ctrl->dataPtr + ctrl->index);
	*p = data;
	ctrl->index += len;

	return 0;
}

int BinaryWriter_SetInt(BinaryWriterControl *ctrl, int data)
{
	int len = 4;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	int *p = (int *)(ctrl->dataPtr + ctrl->index);
	*p = data;
	ctrl->index += len;

	return 0;
}

int BinaryWriter_SetLong(BinaryWriterControl *ctrl, ULONG64 data)
{
	int len = 8;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	ULONG64 *p = (ULONG64 *)(ctrl->dataPtr + ctrl->index);
	*p = data;
	ctrl->index += len;

	return 0;
}

int BinaryWriter_SetDouble(BinaryWriterControl *ctrl, double data)
{
	int len = 8;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	double *p = (double *)(ctrl->dataPtr + ctrl->index);
	*p = data;
	ctrl->index += len;

	return 0;
}

int BinaryWriter_SetString(BinaryWriterControl *ctrl, char *data)
{
	int len = strlen(data)+1;
	if (ctrl->index + len > ctrl->maxLength)
		return -1;

	memcpy(ctrl->dataPtr + ctrl->index, data, len);
	ctrl->index += len;

	return 0;
}
