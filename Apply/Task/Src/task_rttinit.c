#include "task_conf.h"

#include <rthw.h>
#include <rtthread.h>

static void Thread_Main(void *parameter);
static void Thread_UserInit(void *parameter);
static void Thread_PCListner(void *parameter);
static void Thread_FATFSDataSave(void *parameter);
static void Thread_FATFSDataRead(void *parameter);
static void Thread_Sleep(void *parameter);
static void Thread_DataTx(void *parameter);
static void Thread_PCTx(void *parameter);

#define ucThreadNum	8
static tagRTTThreadInfo_T s_tRTTInfo[ucThreadNum] =
{
	/* �߳���		��ں���					���� 		ջ��С	���ȼ�	ʱ��Ƭ	�߳�ָ��	*/
	{"Main",		Thread_Main,				RT_NULL,	512,	2,		5, 		RT_NULL},
	{"UserInit",	Thread_UserInit,			RT_NULL,	1024,	1,		5, 		RT_NULL},
	{"PCLis",		Thread_PCListner, 			RT_NULL,	512,	3,		5, 		RT_NULL},
	{"FATFSSa",		Thread_FATFSDataSave,		RT_NULL,	512,	5,		10, 	RT_NULL},
	{"FATFSRe",		Thread_FATFSDataRead,		RT_NULL,	512,	5,		10, 	RT_NULL},
	{"Sleep",		Thread_Sleep,				RT_NULL,	512,	4,		10, 	RT_NULL},
	{"DataTx",		Thread_DataTx,				RT_NULL,	512,	4,		10, 	RT_NULL},
	{"PCTx",		Thread_PCTx,				RT_NULL,	512,	3,		10, 	RT_NULL}
};

static void Thread_PCTx(void *parameter)
{
	while(1)
	{		
		Task_PCTx();
		
		rt_thread_resume(s_tRTTInfo[5].pThread);	/* �̻߳��� */
		
		rt_thread_suspend(s_tRTTInfo[7].pThread);	/* �̹߳��� */
		rt_schedule();								/* �߳��л� */
	}
}

static void Thread_DataTx(void *parameter)
{
	while(1)
	{		
		rt_thread_suspend(s_tRTTInfo[6].pThread);	/* �̹߳��� */
		rt_schedule();								/* �߳��л� */
		
		Task_DataTx();
		
		rt_thread_resume(s_tRTTInfo[5].pThread);	/* �����̻߳��� */
	}
}

static void Thread_Sleep(void *parameter)
{
	while(1)
	{		
		rt_thread_suspend(s_tRTTInfo[5].pThread);	/* �̹߳��� */
		rt_schedule();								/* �߳��л� */
		
		printf("Sleep Start!!!\r\n");
		Task_Sleep();
		printf("Sleep End!!!\r\n");
		
		rt_thread_resume(s_tRTTInfo[7].pThread);	/* �̻߳��� */
	}
}

static void Thread_FATFSDataRead(void *parameter)
{
	while(1)
	{
		rt_thread_suspend(s_tRTTInfo[4].pThread);	/* �̹߳��� */
		rt_schedule();							/* �߳��л� */
		
		Task_FATFSDataRead();					/* ���ݴ洢����ʵ�� */
	}
}

static void Thread_FATFSDataSave(void *parameter)
{
	while(1)
	{
		rt_thread_suspend(s_tRTTInfo[3].pThread);	/* �̹߳��� */
		rt_schedule();							/* �߳��л� */
		
		Task_FATFSDataSave();					/* ���ݴ洢����ʵ�� */
	}
}

static void Thread_PCListner(void *parameter)
{
	while (1)
    {
		/* ����һ����ֹ���� */
		/* �ٽ������� */
		rt_enter_critical();	/* �����ٽ�������ֹ���� */
        
		rt_exit_critical();		/* �˳��ٽ��������������� */
		
		/* �ٽ������� */
        rt_thread_mdelay(500);
    }
}

static void Thread_UserInit(void *parameter)
{	
	Task_UserInit();
	
	printf("ִ���߳�->�û���ʼ��\r\n");
}

static void Thread_Main(void *parameter)
{
	while(1)
	{
		rt_thread_mdelay(1000);
	}
}

void RTT_ThreadCreate(void)
{
	uint8_t index;
	
	for(index = 0; index < ucThreadNum; index++)
	{
		s_tRTTInfo[index].pThread = rt_thread_create(
										s_tRTTInfo[index].ucpName,
										s_tRTTInfo[index].fun,
										s_tRTTInfo[index].parameter,
										s_tRTTInfo[index].ulStackSize,
										s_tRTTInfo[index].ucPriority,
										s_tRTTInfo[index].ucTick
										);
		
		if(s_tRTTInfo[index].pThread != RT_NULL)
			rt_thread_startup(s_tRTTInfo[index].pThread);
	}
}

void RTT_ThreadDispatch(uint8_t _ucIndex)
{
	rt_thread_resume(s_tRTTInfo[_ucIndex].pThread);	/* �̻߳��� */
}
