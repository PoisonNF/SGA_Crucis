#include "threadpool.h"

void (*ucNowThread)();
void (*ucNextThread)();

void ThreadPool(void)
{
//	ucNowThread = Thread_Sleep;	/* Ĭ���߳� */
	
	while(1)
	{
		ucNowThread();	/* ִ�е�ǰ�߳� */
		ucNowThread = ucNextThread;
	}
}
