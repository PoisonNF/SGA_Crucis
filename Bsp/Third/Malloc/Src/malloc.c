#include "malloc.h"	 

/* �ڴ�����趨 */
#define MEM_BLOCK_SIZE			32  	  						/* �ڴ���СΪ32�ֽ� */
#define MEM_MAX_SIZE			35*1024  						/* �������ڴ� 35K */
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	/* �ڴ���С */

static unsigned char UT_Mem_Perused(void);					/* ���ڴ�ʹ����(��/�ڲ�����) */

static __align(4) unsigned char s_mem_base[MEM_MAX_SIZE];				/* SRAM�ڴ�أ�(4�ֽڶ���) */
static unsigned short s_mem_mapBase[MEM_ALLOC_TABLE_SIZE];			/* SRAM�ڴ��MAP */   
static const unsigned int s_mem_list_size = MEM_ALLOC_TABLE_SIZE;		/* �ڴ���С */
static const unsigned int s_mem_piece_size = MEM_BLOCK_SIZE;				/* �ڴ�ֿ��С */
static const unsigned int s_mem_size = MEM_MAX_SIZE;					/* �ڴ��ܴ�С */

/* �ڴ��������� */
struct _mem_allocation_dev
{
	void 			(*init)(void);		/* ��ʼ�� */
	unsigned char	(*perused)(void);	/* �ڴ�ʹ���� */
	unsigned char	*s_mem_base;				/* �ڴ�� */
	unsigned short	*memMap;				/* �ڴ����״̬�� */
	unsigned char	memRdy;					/* �ڴ�����Ƿ���� */
};

/* �ڴ��������� */
static struct _mem_allocation_dev s_mem_allocation_dev=
{
	UT_Mem_Init,		/* �ڴ��ʼ�� */
	UT_Mem_Perused,		/* �ڴ�ʹ���� */
	s_mem_base,			/* �ڴ�� */
	s_mem_mapBase,			/* �ڴ����״̬�� */
	0,  				/* �ڴ����δ���� */
};

/**
 * @brief �ڴ渳ֵ
 * @param *_des-Ŀ�ĵ�ַ
 * @param *_src-Դ��ַ
 * @param _lenth-��Ҫ���Ƶ��ڴ泤��(�ֽ�Ϊ��λ)
 * @retval null
*/
static void UT_Mem_Copy(void *_des,void *_src,unsigned int _lenth)  
{  
    unsigned char *xdes=_des;
	unsigned char *xsrc=_src; 
    while(_lenth--)*xdes++=*xsrc++;  
}  

/**
 * @brief �����ڴ�
 * @param *_src-Դ��ַ
 * @param _val-Ҫ���õ�ֵ
 * @param _size-��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
 * @retval null
*/
static void UT_Mem_Set(void *_src,unsigned char _val,unsigned int _size)  
{  
    unsigned char *xs = _src;  
    while(_size--)*xs++=_val; 
}	  

/**
 * @brief �ڴ����
 * @param _size-Ҫ������ڴ��С(�ֽ�)
 * @retval 0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ 
*/
static unsigned int UT_Mem_MyAllocation(unsigned int _size)  
{  
    signed long offset=0;  
    unsigned short nmemb;						/* ��Ҫ���ڴ����  */
	unsigned short cmemb=0;						/* �������ڴ���� */
    unsigned int i;  
    if(!s_mem_allocation_dev.memRdy)
		s_mem_allocation_dev.init();						/* δ��ʼ��,��ִ�г�ʼ�� */
    if(_size==0)
		return 0XFFFFFFFF;						/* ����Ҫ���� */
	
    nmemb=_size/s_mem_piece_size;  					/* ��ȡ��Ҫ����������ڴ���� */
	
    if(_size%s_mem_piece_size)
		nmemb++;  
    for(offset=s_mem_list_size-1;offset>=0;offset--)	/* ���������ڴ������  */ 
    {     
		if(!s_mem_allocation_dev.memMap[offset])
			cmemb++;	/* �������ڴ�������� */
		else 
			cmemb=0;							/* �����ڴ������ */
		
		if(cmemb==nmemb)						/* �ҵ�������nmemb�����ڴ�� */
		{
            for(i=0;i<nmemb;i++)  				/* ��ע�ڴ��ǿ�  */
            {  
                s_mem_allocation_dev.memMap[offset+i]=nmemb;  
            }  
            return (offset*s_mem_piece_size);			/* ����ƫ�Ƶ�ַ   */
		}
    }  
    return 0XFFFFFFFF;/* δ�ҵ����Ϸ����������ڴ��  */ 
} 

/**
 * @brief �ͷ��ڴ�
 * @param _offset-�ڴ��ַƫ��
 * @retval 0,�ͷųɹ�;1,�ͷ�ʧ��; 
*/
static unsigned char UT_Mem_Clear(unsigned int _offset)  
{  
    int i;  
    if(!s_mem_allocation_dev.memRdy)					/* δ��ʼ��,��ִ�г�ʼ�� */
	{
		s_mem_allocation_dev.init();    
        return 1;							/* δ��ʼ�� */ 
    }  
    if(_offset<s_mem_size)						/* ƫ�����ڴ���� */
    {  
        int index=_offset/s_mem_piece_size;		/* ƫ�������ڴ����� */
        int nmemb=s_mem_allocation_dev.memMap[index];	/* �ڴ������ */
        for(i=0;i<nmemb;i++)  				/* �ڴ������ */
        {  
            s_mem_allocation_dev.memMap[index+i]=0;  
        }
        return 0;  
    }
	else 
		return 2;							/* ƫ�Ƴ����� */
}  

/**
 * @brief �ڴ�����ʼ��
 * @retval null
*/
void UT_Mem_Init(void)  
{  
    UT_Mem_Set(s_mem_allocation_dev.memMap, 0,s_mem_list_size*2);//�ڴ�״̬����������  
	UT_Mem_Set(s_mem_allocation_dev.s_mem_base, 0,s_mem_size);	//�ڴ��������������  
	s_mem_allocation_dev.memRdy=1;						//�ڴ�����ʼ��OK  
}  

/**
 * @brief ��ȡ�ڴ�ʹ����
 * @retval ����ֵ:ʹ����(0~100)
*/
unsigned char UT_Mem_Perused(void)  
{  
    unsigned int used=0;  
    unsigned int i;  
	
    for(i=0;i<s_mem_list_size;i++)  
    {  
        if(s_mem_allocation_dev.memMap[i])
			used++; 
    }
	
    return (used*100)/(s_mem_list_size);  
}  

/**
 * @brief �ͷ��ڴ�(�ⲿ����) 
 * @param *_ptr-�ڴ��׵�ַ
 * @retval null
*/
void UT_Mem_Free(void *_ptr)  
{  
	unsigned int offset;  
    if(_ptr==0)
		return;				/* ��ַΪ0 */  
 	offset=(unsigned int)_ptr-(unsigned int)s_mem_allocation_dev.s_mem_base;  
    UT_Mem_Clear(offset);	/* �ͷ��ڴ� */     
}  

/**
 * @brief �����ڴ�(�ⲿ����) 
 * @param _size-�ڴ��С(�ֽ�)
 * @retval ���䵽���ڴ��׵�ַ
*/
void *UT_Mem_Allocation(unsigned int _size)  
{  
    unsigned int offset;  									      
	offset=UT_Mem_MyAllocation(_size);  	   				   
    if(offset==0XFFFFFFFF)
		return 0;  
    else 
		return (void*)((unsigned int)s_mem_allocation_dev.s_mem_base+offset);  
}  

/**
 * @brief ���·����ڴ�(�ⲿ����) 
 * @param *_ptr-���ڴ��׵�ַ
 * @param _size-�ڴ��С(�ֽ�)
 * @retval �·��䵽���ڴ��׵�ַ
*/
void *UT_Mem_ReAllocation(void *_ptr,unsigned int _size)  
{  
    unsigned int offset;  
    offset=UT_Mem_MyAllocation(_size);  
    if(offset==0XFFFFFFFF)
		return 0;     
    else  
    {  									   
	    UT_Mem_Copy((void*)((unsigned int)s_mem_allocation_dev.s_mem_base+offset),_ptr,_size);	//�������ڴ����ݵ����ڴ�   
        UT_Mem_Free(_ptr);  											  	//�ͷž��ڴ�
        return (void*)((unsigned int)s_mem_allocation_dev.s_mem_base+offset);  			//�������ڴ��׵�ַ
    }  
}
