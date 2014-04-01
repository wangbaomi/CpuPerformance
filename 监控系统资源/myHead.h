#ifndef _HEADERNAME_H
#define _HEADERNAME_H

#include <windows.h>
#include <Pdh.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

#ifndef MALLOC_FAIL
#define MALLOC_FAIL -1
#endif

#ifndef OPEN_SUCCESS
#define OPEN_SUCCESS 0
#endif

#ifndef OPEN_FAIL
#define OPEN_FAIL -2
#endif

#ifndef ADD_SUCCESS
#define ADD_SUCCESS 0
#endif

#ifndef ADD_FAIL
#define ADD_FAIL -3
#endif

#pragma comment (lib, "Pdh.lib")

typedef struct
{
	PDH_STATUS status;
	HQUERY hQuery;
	HCOUNTER hCounter;
	PDH_FMT_COUNTERVALUE DisplayValue;
	DWORD dwCounterType;
	//char Path[50];
}PDH;

void init(PDH *pdhvar);
int OpenQuery(PDH *pdhvar);

int AddProcessorTimeCounter(PDH *processorTime);
int AddUserTimeCounter(PDH *userTime);
int AddIdleTimeCounter(PDH *idleTime);
int AddInterruptTimeCounter(PDH *interruptTime);
int AddDpcTimeCounter(PDH *dpcTime);
int AddDpcRateCounter(PDH *dpcRate);
int AddDpcsCounter(PDH *dpcs);
int AddInterruptsCounter(PDH *interrupts);


void CollectQueryData(PDH *pdhvar1, PDH *pdhvar2, PDH *pdhvar3, PDH *pdhvar4, PDH *pdhvar5, PDH *pdhvar6, PDH *pdhvar7, PDH *pdhvar8);
void GetFormattedCounterValue(PDH *pdhvar);

#endif