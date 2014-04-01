#include "myHead.h"

//初始化结构体
void init(PDH *pdhvar)
{
	//pdhvar = (PDH *)malloc(sizeof(PDH));
	pdhvar->status = ERROR_SUCCESS;
	pdhvar->hQuery = NULL;
	pdhvar->hCounter = NULL;
	pdhvar->dwCounterType = 0;
}

//新建查询，成功返回0，失败返回-2
int OpenQuery(PDH *pdhvar)
{
	pdhvar->status = PdhOpenQuery(NULL, 0, &pdhvar->hQuery);    //打开计数器对象  
	if (ERROR_SUCCESS == pdhvar->status)  
	{   
		return OPEN_SUCCESS;
	}
	return OPEN_FAIL;
}
//PdhAddCounter中counterpath的类型跟char*的关系没搞明白
//添加processorTime计数器，成功返回0， 失败返回-3
int AddProcessorTimeCounter(PDH *processorTime)
{
	processorTime->status = PdhAddCounter(processorTime->hQuery, _T("\\Processor(_Total)\\% Processor Time"), 0, &processorTime->hCounter);
	if (ERROR_SUCCESS == processorTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加userTime计数器，成功返回0， 失败返回-3
int AddUserTimeCounter(PDH *userTime)
{
	userTime->status = PdhAddCounter(userTime->hQuery, _T("\\Processor(_Total)\\% User Time"), 0, &userTime->hCounter);
	if (ERROR_SUCCESS == userTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加idleTime计数器，成功返回0， 失败返回-3
int AddIdleTimeCounter(PDH *idleTime)
{
	idleTime->status = PdhAddCounter(idleTime->hQuery, _T("\\Processor(_Total)\\% Idle Time"), 0, &idleTime->hCounter);
	if (ERROR_SUCCESS == idleTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}
//添加interruptTime计数器
int AddInterruptTimeCounter(PDH *interruptTime)
{
	interruptTime->status = PdhAddCounter(interruptTime->hQuery, _T("\\Processor(_Total)\\% Interrupt Time"), 0, &interruptTime->hCounter);
	if (ERROR_SUCCESS == interruptTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加dpcTime计数器
int AddDpcTimeCounter(PDH *dpcTime)
{
	dpcTime->status = PdhAddCounter(dpcTime->hQuery, _T("\\Processor(_Total)\\% DPC Time"), 0, &dpcTime->hCounter);
	if (ERROR_SUCCESS == dpcTime->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加dpcRate计数器
int AddDpcRateCounter(PDH *dpcRate)
{
	dpcRate->status = PdhAddCounter(dpcRate->hQuery, _T("\\Processor(_Total)\\DPC Rate"), 0, &dpcRate->hCounter);
	if (ERROR_SUCCESS == dpcRate->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加dpcs计数器
int AddDpcsCounter(PDH *dpcs)
{
	dpcs->status = PdhAddCounter(dpcs->hQuery, _T("\\Processor(_Total)\\DPCs Queued/sec"), 0, &dpcs->hCounter);
	if (ERROR_SUCCESS == dpcs->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}

//添加interrupts计数器
int AddInterruptsCounter(PDH *interrupts)
{
	interrupts->status = PdhAddCounter(interrupts->hQuery, _T("\\Processor(_Total)\\Interrupts/sec"), 0, &interrupts->hCounter);
	if (ERROR_SUCCESS == interrupts->status)
	{
		return ADD_SUCCESS;
	}
	return ADD_FAIL;
}


//收集数据
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

//提取数据
void GetFormattedCounterValue(PDH *pdhvar)
{
	pdhvar->status = PdhGetFormattedCounterValue(pdhvar->hCounter,PDH_FMT_DOUBLE,&pdhvar->dwCounterType, &pdhvar->DisplayValue);
}