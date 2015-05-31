#include "stdafx.h"
#include "Requests.h"
#include "binaryReader.h"
#include <stdio.h>


/*****************************************************************
*
*	Common
*
******************************************************************/
int RequestAnalyze(char *data, int length, RequestData *req)
{
	BinaryReaderControl ctrl;
	int type;

	memset(req, 0, sizeof(*req));

	BinaryReaderInit(data, length, &ctrl);
	
	BinaryReaderGetInt(&ctrl, &type);
	req->orderType = (RequestType)type;

	switch (req->orderType)
	{
		case RequestType_Test:
			GetTestRequest(&ctrl, &req->data.testReq);
			break;
		case RequestType_RateByTime:
			GetRatesByTimeRequest(&ctrl, &req->data.rateByTimeReq);
			break;
		case RequestType_SendOrder:
			GetSenderOrderRequest(&ctrl, &req->data.sendOrderReq);
			break;
		case RequestType_SymbolNameList:
			GetSymbolNameListRequest(&ctrl, &req->data.symbolNameListReq);
			break;
		case RequestType_None:
		default:
			printf("RequestAnalyze: Wrong type!\r\n");
			break;
	}

	return 0;
}



