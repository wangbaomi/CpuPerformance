#include "myHead.h"



int main()
{

	//processorTime:%Processor Time(cpuռ����); userTime:%User Time(�û�̬cpuռ����); systemTime:procTime-userTime(ϵͳ̬cpuռ����); 
	//idleTime:%Idle Time(cpu������); interruptTime:%Interrupt Time(cpu�����ж�����İٷֱ�); dpcTime:%DPC Time(cpu����dpc����İٷֱ�);
	//dpcRate:DPC Rate(DPC����); dpcs:DPCs Queued/sec(DPC���г���); interrupts:Interrupts/sec(�ж���ӦƵ��);

	PDH *processorTime, *userTime, *systemTime, *idleTime, *interruptTime, *dpcTime, *dpcRate, *dpcs, *interrupts;
	time_t newTime;
	struct tm *sysTime;

	FILE *fp = NULL;
	char logName[19] = "";

	//��ʼ��
	if ((processorTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpuռ����-����������ʧ��!\n");
		return MALLOC_FAIL;
	}
	if ((userTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("�û�̬cpuռ����-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((idleTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu������-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((interruptTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu�����ж�����İٷֱ�-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((dpcTime = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("cpu����dpc����İٷֱ�-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((dpcRate = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("DPC����-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((dpcs = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("DPC���г���-����������ʧ��!\n");
		return MALLOC_FAIL;
	}

	if ((interrupts = (PDH *)malloc(sizeof(PDH))) == NULL)
	{
		printf("�ж���ӦƵ��-����������ʧ��!\n");
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


	//�½���ѯ
	if (OpenQuery(processorTime) == OPEN_FAIL)
	{
		printf("cpuռ����-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}

	if (OpenQuery(userTime) == OPEN_FAIL)
	{
		printf("�û�̬cpuռ����-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(idleTime) == OPEN_FAIL)
	{
		printf("cpu������-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(interruptTime) == OPEN_FAIL)
	{
		printf("cpu�����ж�����İٷֱ�-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcTime) == OPEN_FAIL)
	{
		printf("cpu����dpc����İٷֱ�-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcRate) == OPEN_FAIL)
	{
		printf("DPC����-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(dpcs) == OPEN_FAIL)
	{
		printf("DPC���г���-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}
	if (OpenQuery(interrupts) == OPEN_FAIL)
	{
		printf("�ж���ӦƵ��-�½���ѯʧ��!\n");
		return OPEN_FAIL;
	}

	//��Ӽ�����
	if (AddProcessorTimeCounter(processorTime) == ADD_FAIL)
	{
		printf("cpuռ����-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddUserTimeCounter(userTime) == ADD_FAIL)
	{
		printf("�û�̬cpuռ����-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddIdleTimeCounter(idleTime) == ADD_FAIL)
	{
		printf("cpu������-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddInterruptTimeCounter(interruptTime) == ADD_FAIL)
	{
		printf("cpu�����ж�����İٷֱ�-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddDpcTimeCounter(dpcTime) == ADD_FAIL)
	{
		printf("cpu����dpc����İٷֱ�-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddDpcRateCounter(dpcRate) == ADD_FAIL)
	{
		printf("DPC����-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddDpcsCounter(dpcs) == ADD_FAIL)
	{
		printf("DPC���г���-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}
	if (AddInterruptsCounter(interrupts) == ADD_FAIL)
	{
		printf("�ж���ӦƵ��-��Ӽ�����ʧ��!\n");
		return ADD_FAIL;
	}

	//�ռ���һ������
	CollectQueryData(processorTime, userTime, idleTime, interruptTime, dpcTime, dpcRate, dpcs, interrupts);

	//printf("\t\t\tCPUռ����(%%)\t�û�̬CPUռ����(%%)\tcpu������(%%)\tcpu�����ж�����İٷֱ�(%%)\tcpu����dpc����İٷֱ�(%%)\tDPC����(%%)\tDPC���г���()\t�ж���ӦƵ��()\t\n");
	
	//����־�ļ�
	sprintf(logName, "%s.csv","CPU״̬��Ϣ����");
	if ((fp = fopen(logName, "a")) == NULL)
	{
		printf("����־�ļ�ʧ�ܣ�\n");
	}
	else
	{
		//д����־�ļ�	
		fprintf(fp, "Date,Time,%%Processor Time,%%User Time,%%Idle Time,%%Interrupt Time,%%DPC Time,DPC Rate,DPCs Queued/sec,Interrupts/sec,\n");
	}
	//cmd��ӡ
	printf("�����ռ�CPU״̬��Ϣ...\n\n��Ϣ�����ڡ�CPU״̬��Ϣ����.csv����\n\n(��Ctrl+C��������)\n");
	while(1)
	{
		//���1��ˢ��
		Sleep(1000);
		//�ռ��ڶ�������
		CollectQueryData(processorTime, userTime, idleTime, interruptTime, dpcTime, dpcRate, dpcs, interrupts);

		//��ȡ����
		GetFormattedCounterValue(processorTime);
		GetFormattedCounterValue(userTime);
		GetFormattedCounterValue(idleTime);
		GetFormattedCounterValue(interruptTime);
		GetFormattedCounterValue(dpcTime);
		GetFormattedCounterValue(dpcRate);
		GetFormattedCounterValue(dpcs);
		GetFormattedCounterValue(interrupts);

		//��ȡϵͳʱ��
		time(&newTime);
		sysTime = localtime(&newTime);

		////����־�ļ�
		//sprintf(logName, "log_%d%02d%02d%02d.txt",
		//	1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour);
		//if ((fp = fopen(logName, "a")) == NULL)
		//{
		//	printf("����־�ļ�ʧ�ܣ�\n");
		//}
		//else
		//{

		//д����־�ļ�	
		//fprintf(fp, "\t\t\tCPUռ����(%%)\t�û�̬CPUռ����(%%)\tcpu������(%%)\tcpu�����ж�����İٷֱ�(%%)\tcpu����dpc����İٷֱ�(%%)\tDPC����(%%)\tDPC���г���()\t�ж���ӦƵ��()\t\n");
		fprintf(fp, "%d-%02d-%02d,%02d:%02d:%02d,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f\n",
			1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min, sysTime->tm_sec,
			processorTime->DisplayValue.doubleValue, userTime->DisplayValue.doubleValue, idleTime->DisplayValue.doubleValue, 
			interruptTime->DisplayValue.doubleValue, dpcTime->DisplayValue.doubleValue, dpcRate->DisplayValue.doubleValue,
			dpcs->DisplayValue.doubleValue, interrupts->DisplayValue.doubleValue);

		//}
		//��ӡ������̨
		//printf("%d-%02d-%02d %02d:%02d:%02d",
		//	1900+sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min, sysTime->tm_sec);
		//printf("\t%5.1f\t\t%.1f\t\t%7.3f\n", 
		//	processorTime->DisplayValue.doubleValue, userTime->DisplayValue.doubleValue, idleTime->DisplayValue.doubleValue); 
	}
	fclose(fp);

	return 0;
}

