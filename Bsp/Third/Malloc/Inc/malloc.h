#ifndef __MALLOC_H
#define __MALLOC_H
   
void UT_Mem_Init(void);					 //�ڴ�����ʼ������(��/�ڲ�����)
void UT_Mem_Free(void *ptr);  				//�ڴ��ͷ�(�ⲿ����)
void *UT_Mem_Allocation(unsigned int size);				//�ڴ����(�ⲿ����)
void *UT_Mem_ReAllocation(void *ptr,unsigned int size);	//���·����ڴ�(�ⲿ����)
#endif
