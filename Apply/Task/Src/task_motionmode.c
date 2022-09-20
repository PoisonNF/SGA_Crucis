#include "task_conf.h"

#include "bsp_io.h"

/*  
  <���� <���� <����       4          1                P1 = 0.5 * P *cos(��+45��)
 |           |                                  P1 = 0.5 * P *cos(��-225��)
 |           |                      -->         P1 = 0.5 * P *cos(��-135��)
 |           |                                  P1 = 0.5 * P *cos(��-45��)
  ����> ����> ����>       3          2 
 */

/**
 * @brief ˮƽ�������
 * @param P ���ƽ���    P�ķ�ΧΪ[0,560]    ���������ռ�ձ�Ϊ8.9(1780hz)����Сռ�ձ�Ϊ6(1200hz)
 * @param �� ��X��ļн� ��Ϊ[0,360)
 * @retval Pout ����ĸ��ƽ����ķ���������׵�ַ
*/
float *Task_Horizontal_Heading_Calculation(uint16_t P,int ��)
{
    static float Pout[4];
    if(0 < P <= 560 && 0 < �� < 360)
    {
        Pout[0] = 0.5*P*cos((��+45)*pi/180);     //P1���ƽ���
        Pout[1] = 0.5*P*cos((��-225)*pi/180);    //P2���ƽ���
        //Pout[2] = 0.5*P*cos((��-135)*pi/180);    //P3���ƽ���
        //Pout[3] = 0.5*P*cos((��-45)*pi/180);     //P4���ƽ���
        Pout[2] = -Pout[0];
        Pout[3] = -Pout[1];
    }
    return Pout;
}



