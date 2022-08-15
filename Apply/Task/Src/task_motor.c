#include "task_conf.h"

#include "bsp_io.h"


/**
 * @brief �����ʼ��
 * @param null
 * @retval null
*/
void Task_Motor_Init(void)
{
	Drv_Delay_Ms(2000);		/* ��ʼͣת�źź�ȴ��ȶ� */
	
	/* ��ת�����ţ�10%ռ�ձ� */
	//Drv_PWM_DutyfactorSet(&tPWMDemo[0], 10);
	//Drv_Delay_Ms(2000);
	
	/* ��ת�����ţ�5%ռ�ձ� */
	//Drv_PWM_DutyfactorSet(&tPWMDemo[0], 5);
	//Drv_Delay_Ms(2000);
	
	/* ͣת��7.5%ռ�ձ� */
	Drv_PWM_DutyfactorSet(&tPWMDemo[0], 7.5);
	Drv_PWM_DutyfactorSet(&tPWMDemo[1], 7.5);
	Drv_PWM_DutyfactorSet(&tPWMDemo[2], 7.5);
	Drv_PWM_DutyfactorSet(&tPWMDemo[3], 7.5);
	Drv_Delay_Ms(4000);
}

/**
 * @brief ���ת�������Ӻ���
 * @param index ѡ�񼸺��ƽ���
 * @param _fVal ռ�ձȴ�С	_fVal������Ϊ2.5-12.5��7.5ֹͣ
							2.5-7.5 ��ʱ����ת 7.5-12.5 ˳ʱ����ת
 * @retval null
*/
void Task_Motor_SpeedSet(int index,float _fVal)
{
	Drv_PWM_DutyfactorSet(&tPWMDemo[index-1], _fVal);
}	

/**
 * @brief �����ʼ����
 * @param index ѡ�񼸺��ƽ���
 * @param _fVal ռ�ձȴ�С
 * @retval null
*/
void Task_Motor_Start(int index,float _fVal)
{
	/* ��������ٶ����� */
	Task_Motor_SpeedSet(index,_fVal);
}

/**
 * @brief ���ֹͣ����
 * @param index ѡ�񼸺��ƽ���
 * @param _fVal ռ�ձȴ�С
 * @retval null
*/
void Task_Motor_Stop(int index)
{
	/* ��������ٶ����� */
	Drv_PWM_DutyfactorSet(&tPWMDemo[index-1], 7.5);
}
