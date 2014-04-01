#include "myHead.h"

//��ʼ���ṹ��
void init(PDH *pdhvar)
{
	//pdhvar = (PDH *)malloc(sizeof(PDH));
	pdhvar->status = ERROR_SUCCESS;
	pdhvar->hQuery = NULL;
	pdhvar->hCounter = NULL;
	pdhvar->dwCounterType = 0;
}

//�½���ѯ���ɹ�����0��ʧ�ܷ���-2
int OpenQuery(PDH *pdhvar)
{
	pdhvar->status = PdhOpenQuery(NULL, 0, &pdhvar->hQuery);    //�򿪼���������  
	if (ERROR_SUCCESS == pdhvar->status)  
	{   
		return OPEN_SUCCESS;
	}
	return OPEN_FAIL;
}
//PdhAddCounter��counterpath�����͸�char*�Ĺ�ϵû������
//���processorTime���������ɹ�����0�� ʧ�ܷ���-3
int AddProcessorTimeCounter(PDH *processorTime)
{
	processorTime->status = PdhAddCounter(processorTime->hQuery, _T("\\Processor(_Total)\\% Processor Time"), 0, &processorTime->hCounter);
	if (ERROR_SUCCESS == processorTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���userTime���������ɹ�����0�� ʧ�ܷ���-3
int AddUserTimeCounter(PDH *userTime)
{
	userTime->status = PdhAddCounter(userTime->hQuery, _T("\\Processor(_Total)\\% User Time"), 0, &userTime->hCounter);
	if (ERROR_SUCCESS == userTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���idleTime���������ɹ�����0�� ʧ�ܷ���-3
int AddIdleTimeCounter(PDH *idleTime)
{
	idleTime->status = PdhAddCounter(idleTime->hQuery, _T("\\Processor(_Total)\\% Idle Time"), 0, &idleTime->hCounter);
	if (ERROR_SUCCESS == idleTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}
//���interruptTime������
int AddInterruptTimeCounter(PDH *interruptTime)
{
	interruptTime->status = PdhAddCounter(interruptTime->hQuery, _T("\\Processor(_Total)\\% Interrupt Time"), 0, &interruptTime->hCounter);
	if (ERROR_SUCCESS == interruptTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���dpcTime������
int AddDpcTimeCounter(PDH *dpcTime)
{
	dpcTime->status = PdhAddCounter(dpcTime->hQuery, _T("\\Processor(_Total)\\% DPC Time"), 0, &dpcTime->hCounter);
	if (ERROR_SUCCESS == dpcTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���dpcRate������
int AddDpcRateCounter(PDH *dpcRate)
{
	dpcRate->status = PdhAddCounter(dpcRate->hQuery, _T("\\Processor(_Total)\\DPC Rate"), 0, &dpcRate->hCounter);
	if (ERROR_SUCCESS == dpcRate->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���dpcs������
int AddDpcsCounter(PDH *dpcs)
{
	dpcs->status = PdhAddCounter(dpcs->hQuery, _T("\\Processor(_Total)\\DPCs Queued/sec"), 0, &dpcs->hCounter);
	if (ERROR_SUCCESS == dpcs->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//���interrupts������
int AddInterruptsCounter(PDH *interrupts)
{
	interrupts->status = PdhAddCounter(interrupts->hQuery, _T("\\Processor(_Total)\\Interrupts/sec"), 0, &interrupts->hCounter);
	if (ERROR_SUCCESS == interrupts->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}


//�ռ�����
void CollectQueryData(PDH *pdhvar1, PDH *pdhvar2, PDH *pdhvar3, PDH *pdhvar4, PDH *pdhvar5, PDH *pdhvar6, PDH *pdhvar7, PDH *pdhvar8)
{
	PdhCollectQueryData(pdhvar1->hQuery);       
	PdhCollectQueryData(pdhvar2->hQuery);        
	PdhCollectQueryData(pdhvar3->hQuery);
	PdhCollectQueryData(pdhvar4->hQuery); 
	PdhCollectQueryData(pdhvar5->hQuery); 
	PdhCollectQueryData(pdhvar6->hQuery); 
	PdhCollectQueryData(pdhvar7->hQuery); 
	PdhCollectQueryData(pdhvar8->hQuery); 
}

//��ȡ����
void GetFormattedCounterValue(PDH *pdhvar)
{
	pdhvar->status = PdhGetFormattedCounterValue(pdhvar->hCounter,PDH_FMT_DOUBLE,&pdhvar->dwCounterType, &pdhvar->DisplayValue);
}