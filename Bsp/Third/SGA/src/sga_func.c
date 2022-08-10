/****************************************************************************

* Sigma�Ŷ�

* �ļ���: sga_func.c

* ���ݼ�����SGA���ⳣ�ú����ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.0.0a 	2020-02-22	���		�������ļ�
* 1.0.1a 	2020-03-15	���		����SGA_StringToHex����
									�޸�SGA_Function_Query_Subִ���߼��������ͷ���ֵ

****************************************************************************/
#include "sga_func.h"

/**
 * @brief ��ѯһ���ַ���a���Ƿ������һ���ַ���b
 * @param *_ucpStrA---�ַ���a��ַָ��
 * @param _iSrclenth---�ַ���a�ĳ���
 * @param _ucpStrB---�ַ���b��ַָ��
 * @param _ucpStrBlenth---�ַ���b�ĳ���
 * @retval -1---�������ַ���b������---�ַ���b���ַ���a����ʼλ��
*/
tag_StringInfo SGA_Function_Query_Sub(uint8_t *_ucpStrA, uint8_t *_ucpStrB)
{
	uint8_t *ucpSrc; 
	uint8_t *ucpSub;
	uint16_t usNum = 1;
	tag_StringInfo pos = {0,0};
	
	if(!_ucpStrA||!_ucpStrB)
	{
	   return pos;
	}
	/* ����src�ַ��� */
	while(*_ucpStrA)
	{ 
		/* ���������Ӵ� */
		ucpSrc = _ucpStrA;
		ucpSub = _ucpStrB;
		pos.ulIndex++;
		while(*ucpSrc++ == *ucpSub++)
		{
			usNum += 1;
			if(*ucpSub == ':')/*����sub�Ľ���λ�ã�����srcλ��*/
			{
				pos.ucpAddr = ucpSrc + 2;
				pos.ulIndex += usNum;
				return pos;
			}
			
		}
		usNum = 1;
		_ucpStrA++	;
		
	}
	
	return pos; 
}

/**
 * @brief ���ַ���1�е�ָ��λ�ò����ַ���2(ע�ⳤ��)
 * @param *_ucpStrA---�ַ���1��ַָ��
 * @param *_ucpStrB---�ַ���2��ַָ��
 * @param usOffset---ƫ����
 * @retval char*---�ַ���1�ĵ�ַ
*/
#define SGA_INSERT_LENGTH	30
static char ucpInsertBuffer[SGA_INSERT_LENGTH] = {0};
void SGA_Function_Insert_Sub(uint8_t *_ucpStrA, uint8_t *_ucpStrB, uint16_t usOffset)
{
	uint8_t ucLen = 0;
	
	ucLen = strlen((char*)_ucpStrB);
	
	if(usOffset)
	{
		memcpy(ucpInsertBuffer, _ucpStrA, usOffset);
		memcpy(ucpInsertBuffer + usOffset, _ucpStrB, ucLen);
		memcpy(ucpInsertBuffer + usOffset + ucLen, _ucpStrA + usOffset, strlen((char*)_ucpStrA) - usOffset);
	}
	else
	{
		memcpy(ucpInsertBuffer, _ucpStrB, ucLen);
		memcpy(ucpInsertBuffer + ucLen, _ucpStrA, strlen((char*)_ucpStrA));
	}
	
	memcpy(_ucpStrA, ucpInsertBuffer, strlen((char*)_ucpStrA) + ucLen);
	memset(ucpInsertBuffer, 0, SGA_INSERT_LENGTH);
}

/* CRC16У�� start*/
static void S_SGA_Function_InvertUint8(uint8_t *_ucpBuffer, uint8_t *_ucpSrcBuffer)  
{  
    int i;  
    uint8_t ucpTmp[4];  
    ucpTmp[0] = 0;  
    for(i=0;i< 8;i++)  
    {  
      if(_ucpSrcBuffer[0]& (1 << i))  
        ucpTmp[0] |= 1<<(7-i);  
    }  
    _ucpBuffer[0] = ucpTmp[0];       
}  

static void S_SGA_Function_InvertUint16(uint16_t *_ucpBuffer, uint16_t *_ucpSrcBuffer)  
{  
    int i;  
    uint16_t ucpTmp[4];  
    ucpTmp[0] = 0;  
    for(i=0;i< 16;i++)  
    {  
      if(_ucpSrcBuffer[0] & (1 << i))  
        ucpTmp[0] |= 1<<(15 - i);  
    }  
    _ucpBuffer[0] = ucpTmp[0];  
} 

/**
 * @brief Crc16λУ�飨modbus��
 * @param _ucpMsg---��ҪУ������������ַָ��
 * @param _usDataLen---��ҪУ����������鳤��
 * @retval 2�ֽ�CRCУ����
*/
uint16_t SGA_Function_Crc16_Modbus(uint8_t *_ucpMsg, uint16_t _usDataLen)
{
	uint16_t usCRCin = 0xFFFF;  
	uint16_t usCPoly = 0x8005;  
	uint8_t ucChar = 0;  
		
	while (_usDataLen--)     
	{  
		ucChar = *(_ucpMsg++);  
		S_SGA_Function_InvertUint8(&ucChar,&ucChar);  
		usCRCin ^= (ucChar << 8); 
		
		for(int i = 0;i < 8;i++)  
		{  
			if(usCRCin & 0x8000)  
				usCRCin = (usCRCin << 1) ^ usCPoly;  
			else  
				usCRCin = usCRCin << 1;  
		}  
	}  
	
	S_SGA_Function_InvertUint16(&usCRCin,&usCRCin); 
	
	return (usCRCin);
}
/* CRC16У�� end*/

/**
 * @brief �ַ���תHex
 * @param *_ucpStrA---��Ҫת�����ַ���
 * @param _ucLen---ת������
 * @retval uint32_t---ת����Ľ��
*/
uint32_t SGA_StringToHex(uint8_t *_ucpStrA, uint8_t _ucLen )
{
	uint8_t index;
	uint32_t ulRes = 0;

	for(index = 0; index < _ucLen; index++)
		ulRes += (_ucpStrA[index] - '0') << ((_ucLen - index - 1) * 4);

	return ulRes;
}

/**
 * @brief ʮ����תHex��ʾ����23ת��Ϊ0x23��
 * @param _ucDec---��Ҫת����ʮ������
 * @retval uint8_t---ת�����ʮ��������
*/
uint8_t SGA_DecToHex(uint8_t _ucDec)
{
	uint8_t res;
	res = _ucDec + (_ucDec / 10) * 6;	

	return res;
}
