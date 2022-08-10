/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_gpio.c

* ���ݼ�����GPIO�����ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.0.0a 	2020-02-22	���		�������ļ�
* 1.0.1a 	2020-03-16	���		����Drv_GPIO_NVICDisable����

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_GPIO_ENABLE

#define NULL 0

/**
 * @brief д��GPIO״̬
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_Write(tagGPIO_T *_tGPIO, GPIO_PinState _pin)
{
	HAL_GPIO_WritePin(_tGPIO->tGPIOPort, _tGPIO->tGPIOInit.Pin, _pin);
}

/**
 * @brief GPIO����
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_Set(tagGPIO_T *_tGPIO)
{
	HAL_GPIO_WritePin(_tGPIO->tGPIOPort, _tGPIO->tGPIOInit.Pin, GPIO_PIN_SET);
}

/**
 * @brief GPIO����
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_Reset(tagGPIO_T *_tGPIO)
{
	HAL_GPIO_WritePin(_tGPIO->tGPIOPort, _tGPIO->tGPIOInit.Pin, GPIO_PIN_RESET);
}

/**
 * @brief ��ȡGPIO״̬
 * @param _tGPIO---GPIO���
 * @retval Null
*/
GPIO_PinState Drv_GPIO_Read(tagGPIO_T *_tGPIO)
{
	return HAL_GPIO_ReadPin(_tGPIO->tGPIOPort, _tGPIO->tGPIOInit.Pin);
}

/**
 * @brief GPIOʱ�ӳ�ʼ������
 * @param _tGPIO---GPIO���
 * @retval Null 
*/
static void S_GPIO_CLKEnable(tagGPIO_T *_tGPIO) 
{	
	if(_tGPIO->tGPIOPort == GPIOA)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if(_tGPIO->tGPIOPort == GPIOB)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if(_tGPIO->tGPIOPort == GPIOC)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if(_tGPIO->tGPIOPort == GPIOD)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}
	else if(_tGPIO->tGPIOPort == GPIOE)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}
}

/**
 * @brief GPIO�������ú���
 * @param _tGPIO---GPIO���
 * @retval Null
*/
static void S_GPIO_ParamConfig(tagGPIO_T *_tGPIO)
{
	HAL_GPIO_Init(_tGPIO->tGPIOPort, &_tGPIO->tGPIOInit);
}

/**
 * @brief GPIO��ʼ������
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_Init(tagGPIO_T *_tGPIO, uint8_t _ucNum)
{
	uint8_t index;
	
	for(index = 0;index < _ucNum;index++)
	{
		S_GPIO_CLKEnable(&_tGPIO[index]);
		S_GPIO_ParamConfig(&_tGPIO[index]);
	}	 
}

/**
 * @brief GPIOĬ�����ú���
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_DeInit(tagGPIO_T *_tGPIO)
{
	HAL_GPIO_DeInit(_tGPIO->tGPIOPort, _tGPIO->tGPIOInit.Pin);
}

/**
 * @brief GPIO�ж���ѡ����
 * @param _tGPIO---GPIO���
 * @retval IO��Ӧ���ж���
*/
static uint8_t S_GPIO_NVICIRQnSelect(tagGPIO_T *_tGPIO)
{
	if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_0)
		return EXTI0_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_1)
		return EXTI1_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_2)
		return EXTI2_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_3)
		return EXTI3_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_4)
		return EXTI4_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_5)
		return EXTI9_5_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_6)
		return EXTI9_5_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_7)
		return EXTI9_5_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_8)
		return EXTI9_5_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_9)
		return EXTI9_5_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_10)
		return EXTI15_10_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_11)
		return EXTI15_10_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_12)
		return EXTI15_10_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_13)
		return EXTI15_10_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_14)
		return EXTI15_10_IRQn;
	else if(_tGPIO->tGPIOInit.Pin == GPIO_PIN_15)
		return EXTI15_10_IRQn;
	
	return NULL;
}

/**
 * @brief GPIO�жϲ�������
 * @param _tGPIO---GPIO���
 * @retval Null
*/
static void S_GPIO_NVICParamConfig(tagGPIO_T *_tGPIO)
{
	switch(S_GPIO_NVICIRQnSelect(_tGPIO))
	{
		case EXTI0_IRQn:
			HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);
			break;
		case EXTI1_IRQn:
			HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI1_IRQn);
			break;
		case EXTI2_IRQn:
			HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI2_IRQn);
			break;
		case EXTI3_IRQn:
			HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI3_IRQn);
			break;
		case EXTI4_IRQn:
			HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI4_IRQn);
			break;
		case EXTI9_5_IRQn:
			HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
			break;
		case EXTI15_10_IRQn:
			HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 2);
			HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
			break;
		default:
			break;
	}
}

/**
 * @brief GPIO�жϺ���
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_EXTI_IRQHandler(tagGPIO_T *_tGPIO)
{
	HAL_GPIO_EXTI_IRQHandler(_tGPIO->tGPIOInit.Pin);
}

/**
 * @brief GPIO�ж�ʧ�ܺ���
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_NVICDisable(tagGPIO_T *_tGPIO)
{
	__HAL_GPIO_EXTI_CLEAR_IT(_tGPIO->tGPIOInit.Pin);
	HAL_NVIC_DisableIRQ((IRQn_Type)S_GPIO_NVICIRQnSelect(_tGPIO));
}

/**
 * @brief GPIO�жϳ�ʼ������
 * @param _tGPIO---GPIO���
 * @retval Null
*/
void Drv_GPIO_NVICConfig(tagGPIO_T *_tGPIO)
{	
	S_GPIO_NVICParamConfig(_tGPIO);
}
#endif
