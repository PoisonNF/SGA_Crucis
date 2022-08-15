#include "task_conf.h"

#include "bsp_io.h"

/*180����
0.5ms----------------0�ȣ�          2.5
1ms -----------------45�ȣ�         5
1.5ms----------------90�ȣ�         7.5
2ms -----------------135�ȣ�        10
2.5ms ---------------180��          12.5      */

/**
 * @brief �����ʼ������
 * @param null
 * @retval null
*/
void Task_Steer_Init(void)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[4],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[5],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[6],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[7],7.5);
    Drv_Delay_Ms(200);
}


/**
 * @brief ���ת�Ǻ���
 * @param index ѡ�񼸺Ŷ�� 
 * @param ang �Ƕȣ�0�ȡ���180�ȣ�
 * @retval null
*/
void Task_Steer_Angle_Set(int index,int ang)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],ang*10/180+2.5);
}

/**
 * @brief �����0�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_0Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],2.5);
}

/**
 * @brief �����90�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_90Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],7.5);
}

/**
 * @brief �����180�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_180Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],12.5);
}



