#ifndef __DRV_GPIO_H_
#define __DRV_GPIO_H_

#include "drv_hal.h"

typedef struct
{
	GPIO_InitTypeDef 	tGPIOInit;
	GPIO_TypeDef* 		tGPIOPort;
	uint8_t				ulPriority;		/* �ж����ȼ���0-15 */
	uint8_t 			ulSubPriority;	/* �ж������ȼ���0-15 */

	uint8_t				ucMode;			/* ��ӳ�����ò��� @ref ucMode_define*/
}tagGPIO_T;

/** @defgroup ucMode_define  remap
  * @brief GPIO remap
  * @{
  */
#define NO_REMAP 		0	/*������ӳ�����*/
#define PARTIAL_REMAP 	1	/*������ӳ��*/
#define PARTIAL_REMAP2 	2	/*������ӳ��2 ��TIM2����*/
#define FULL_REMAP 		3	/*��ȫ��ӳ��*/

void Drv_GPIO_Set(tagGPIO_T *_tGPIO);
void Drv_GPIO_Reset(tagGPIO_T *_tGPIO);
void Drv_GPIO_Write(tagGPIO_T *_tGPIO, GPIO_PinState _tGPIOPin);
GPIO_PinState Drv_GPIO_Read(tagGPIO_T *_tGPIO);
void Drv_GPIO_Init(tagGPIO_T *_tGPIO, uint8_t _ucNum);
void Drv_GPIO_DeInit(tagGPIO_T *_tGPIO);

void Drv_GPIO_EXTI_IRQHandler(tagGPIO_T *_tGPIO);
void Drv_GPIO_NVICDisable(tagGPIO_T *_tGPIO);
void Drv_GPIO_NVICConfig(tagGPIO_T *_tGPIO);

#endif
