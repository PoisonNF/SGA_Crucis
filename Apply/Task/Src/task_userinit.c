#include "task_conf.h"

#include "bsp_io.h"

void Task_UserInit(void)
{
    Drv_GPIO_Init(demoGPIO, 3);

    Drv_Uart_ITInit(&demoUart);
    printf("UART��ʼ�����!\r\n");

    Drv_GPIO_Reset(&demoGPIO[0]);
    Drv_GPIO_Set(&demoGPIO[0]);
    Drv_GPIO_Set(&demoGPIO[0]);

    Drv_PWM_Init(tPWMDemo,8);
    printf("PWM��ʼ�����!\r\n");
    
    Drv_GPIO_Set(&demoGPIO[0]);
    Drv_GPIO_Reset(&demoGPIO[0]);
    Drv_GPIO_Set(&demoGPIO[0]);
    
    
}
