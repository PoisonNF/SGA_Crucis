#include "bsp_io.h"

/* 
	motor PWM1	PC6							steering engine	RS1	PD12
		  PWM2	PC7											RS2	PD13
		  PWM3	PC8											RS3	PD14
		  PWM4	PC9											RS4	PD15

*/

tagPWM_T tPWMDemo[]=
{
	//motor config
	[0] =	//PWM1
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_6,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[1] =	//PWM2
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_7,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[2] =	//PWM3
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[3] =	//PWM4
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_9,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},

	//steer engine config

	[4] =	//RS1
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_12,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[5] =	//RS2
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[6] =	//RS3
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[7] =	//RS4
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_15,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
};

/* OLEDʾ�� */
tagOLED_T tOLED= 
{
	/* SCL�� */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO���� */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOA,					/* GPIO���� */
	
	/* SDA�� */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO���� */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOA,					/* GPIO���� */
};


/* GPIO���ʾ�� */
tagGPIO_T demoGPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    
};

/* ���ھ��ʾ�� */
tagUART_T demoUart = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO���� */
	.tGPIO[0].AFMode				= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO���� */
	.tGPIO[1].AFMode				= NO_REMAP,					/* GPIO��ӳ�� */
};



