#include "myHead.h"



int main()
{

	//processorTime:%Processor Time(cpu占用率); userTime:%User Time(用户态cpu占用率); systemTime:procTime-userTime(系统态cpu占用率); 
	//idleTime:%Idle Time(cpu空闲率); interruptTime:%Interrupt Time(cpu处理中断请求的百分比); dpcTime:%DPC Time(cpu处理dpc请求的百分比);
	//dpcRate:DPC Rate(DPC比率); dpcs:DPCs Queued/sec(DPC队列长度); interrupts:Interrupts/sec(中断响应频率);

	PDH *processorTime, *userTime, *systemTime, *idleTime, *interruptTime, *dpcTime, *dpcRate, *dpcs, *interrupts;
	time_t newTime;
	struct tm *sysTime;

	FILE *fp = NULL;
	char logName[19] = "";

	//初始化
	if ((processorTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu占用率-计数器分配失败!\n");
		return MALLOC_FAIL;
	}
	if ((userTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("用户态cpu占用率-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((idleTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu空闲率-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((interruptTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu处理中断请求的百分比-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((dpcTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu处理dpc请求的百分比-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((dpcRate = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("DPC比率-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((dpcs = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("DPC队列长度-计数器分配失败!\n");
		return MALLOC_FAIL;
	}

	if ((interrupts = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("中断响应频率-计数器分配失败!\n");
		return MALLOC_FAIL;
	}


	init(processorTime);
	init(userTime);
	init(idleTime);
	init(interruptTime);
	init(dpcTime);
	init(dpcRate);
	init(dpcs);
	init(interrupts);


	//新建查询
	if (OpenQuery(processorTime) == OPEN_FAIL)
	{
		printf("cpu占用率-新建查询失败!\n");
		return OPEN_FAIL;
	}

	if (OpenQuery(userTime) == OPEN_FAIL)
	{
		printf("用户态cpu占用率-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(idleTime) == OPEN_FAIL)
	{
		printf("cpu空闲率-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(interruptTime) == OPEN_FAIL)
	{
		printf("cpu处理中断请求的百分比-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcTime) == OPEN_FAIL)
	{
		printf("cpu处理dpc请求的百分比-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcRate) == OPEN_FAIL)
	{
		printf("DPC比率-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcs) == OPEN_FAIL)
	{
		printf("DPC队列长度-新建查询失败!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(interrupts) == OPEN_FAIL)
	{
		printf("中断响应频率-新建查询失败!\n");
		return OPEN_FAIL;
	}

	//添加计数器
	if (AddProcessorTimeCounter(processorTime) == ADD_FAIL)
	{
		printf("cpu占用率-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddUserTimeCounter(userTime) == ADD_FAIL)
	{
		printf("用户态cpu占用率-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddIdleTimeCounter(idleTime) == ADD_FAIL)
	{
		printf("cpu空闲率-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddInterruptTimeCounter(interruptTime) == ADD_FAIL)
	{
		printf("cpu处理中断请求的百分比-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddDpcTimeCounter(dpcTime) == ADD_FAIL)
	{
		printf("cpu处理dpc请求的百分比-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddDpcRateCounter(dpcRate) == ADD_FAIL)
	{
		printf("DPC比率-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddDpcsCounter(dpcs) == ADD_FAIL)
	{
		printf("DPC队列长度-添加计数器失败!\n");
		return ADD_FAIL;
	}
	if (AddInterruptsCounter(interrupts) == ADD_FAIL)
	{
		printf("中断响应频率-添加计数器失败!\n");
		return ADD_FAIL;
	}

	//收集第一次数据
	CollectQueryData(processorTime, userTime, idleTime, interruptTime, dpcTime, dpcRate, dpcs, interrupts);

	//printf("\t\t\tCPU占用率(%%)\t用户态CPU占用率(%%)\tcpu空闲率(%%)\tcpu处理中断请求的百分比(%%)\tcpu处理dpc请求的百分比(%%)\tDPC比率(%%)\tDPC队列长度()\t中断响应频率()\t\n");
	
	//打开日志文件
	sprintf(logName, "%s.csv","CPU状态信息数据");
	if ((fp = fopen(logName, "a")) == NULL)
	{
		printf("打开日志文件失败！\n");
	}
	else
	{
		//写入日志文件	
		fprintf(fp, "Date,Time,%%Processor Time,%%User Time,%%Idle Time,%%Interrupt Time,%%DPC Time,DPC Rate,DPCs Queued/sec,Interrupts/sec,\n");
	}
	//cmd打印
	printf("正在收集CPU状态信息...\n\n信息保存在《CPU状态信息数据.csv》中\n\n(按Ctrl+C结束程序)\n");
	while(1)
	{
		//间隔1秒刷新
		Sleep(1000);
		//收集第二次数据
		CollectQueryData(processorTime, userTime, idleTime, interruptTime, dpcTime, dpcRate, dpcs, interrupts);

		//提取数据
		GetFormattedCounterValue(processorTime);
		GetFormattedCounterValue(userTime);
		GetFormattedCounterValue(idleTime);
		GetFormattedCounterValue(interruptTime);
		GetFormattedCounterValue(dpcTime);
		GetFormattedCounterValue(dpcRate);
		GetFormattedCounterValue(dpcs);
		GetFormattedCounterValue(interrupts);

		//获取系统时间
		time(&newTime);
		sysTime = localtime(&newTime);

		////打开日志文件
		//sprintf(logName, "log_%d%02d%02d%02d.txt",
		//	1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour);
		//if ((fp = fopen(logName, "a")) == NULL)
		//{
		//	printf("打开日志文件失败！\n");
		//}
		//else
		//{

		//写入日志文件	
		//fprintf(fp, "\t\t\tCPU占用率(%%)\t用户态CPU占用率(%%)\tcpu空闲率(%%)\tcpu处理中断请求的百分比(%%)\tcpu处理dpc请求的百分比(%%)\tDPC比率(%%)\tDPC队列长度()\t中断响应频率()\t\n");
		fprintf(fp, "%d-%02d-%02d,%02d:%02d:%02d,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f\n",
			1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min, sysTime->tm_sec,
			processorTime->DisplayValue.doubleValue, userTime->DisplayValue.doubleValue, idleTime->DisplayValue.doubleValue, 
			interruptTime->DisplayValue.doubleValue, dpcTime->DisplayValue.doubleValue, dpcRate->DisplayValue.doubleValue,
			dpcs->DisplayValue.doubleValue, interrupts->DisplayValue.doubleValue);

		//}
		//打印到控制台
		//printf("%d-%02d-%02d %02d:%02d:%02d",
		//	1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min, sysTime->tm_sec);
		//printf("\t%5.1f\t\t%.1f\t\t%7.3f\n", 
		//	processorTime->DisplayValue.doubleValue, userTime->DisplayValue.doubleValue, idleTime->DisplayValue.doubleValue); 
	}
	fclose(fp);

	return 0;
}

