#ifndef __DRV_UART_H_
#define __DRV_UART_H_

#include "drv_hal_conf.h"

/* �����豸�ṹ�� */
typedef struct
{
	UART_HandleTypeDef 	tUARTHandle;	/* STM32�ڲ������豸ָ�� */
	tagGPIO_T			tGPIO[2];
	uint8_t				ulPriority;		/* �ж����ȼ���0-15 */
	uint8_t 			ulSubPriority;	/* �ж������ȼ���0-15 */
}tagUART_T;

void Drv_Uart_ITInit(tagUART_T *_tUART);
void Drv_Uart_Transmit(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize);
void Drv_Uart_ReceIT_Enable(tagUART_T *_tUART, uint8_t *_ucpBuffer, uint16_t _uspSize);

void Drv_Uart_IRQHandler(tagUART_T *_tUART);

#endif
