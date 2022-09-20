/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_oled.c

* ���ݼ�����4��OLED������SSD1306��
			��I/O����ѡ������ΪSCL��SDA��ʵ��OLED�������������ֿ�6*8�Լ�8*16.
			6*8�ַ�ռһҳ����y = 1
			8*16�ַ�ռ��ҳ����y = 2 
* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.1.5  2022-09-08   �����	�������ļ�

****************************************************************************/
#include "ocd_oled.h"
#include "ocd_oled_font.h"

/**
 * @brief 	��SSD1306��д��һ���ֽ����ݻ�������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	dat-����
 * @param 	cmd-����/����   OLED_CMD(0)����;OLED_DATA(1)����;
 * @retval	NULL
 */
static void OLED_WR_Byte(tagOLED_T *_tOLED,uint8_t dat,uint8_t cmd)
{
    Drv_IICSoft_Start(&_tOLED->tIIC);
    Drv_IICSoft_SendByte(&_tOLED->tIIC,0x78);
    Drv_IICSoft_WaitAck(&_tOLED->tIIC);
    if(cmd)
    {
        /* д������ */
        Drv_IICSoft_SendByte(&_tOLED->tIIC,0x40);
    }
    else
    {
        /* д������ */
        Drv_IICSoft_SendByte(&_tOLED->tIIC,0x00);
    }
    Drv_IICSoft_WaitAck(&_tOLED->tIIC);
    Drv_IICSoft_SendByte(&_tOLED->tIIC,dat);
    Drv_IICSoft_WaitAck(&_tOLED->tIIC);
    Drv_IICSoft_Stop(&_tOLED->tIIC);
}


/******************************************* ������OLED������غ��� ************************************************/
/**
 * @brief 	OLED��ʾ��������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	NULL
 * @retval	NULL
 */
void OCD_OLED_DisplayON(tagOLED_T *_tOLED)
{
    OLED_WR_Byte(_tOLED,0x8D,OLED_CMD);//SET DCDC����
    OLED_WR_Byte(_tOLED,0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(_tOLED,0XAF,OLED_CMD);  //DISPLAY ON
}

/**
 * @brief 	OLED��ʾ�رպ���
 * @param   *_tOLED-OLED�ṹ��
 * @param 	NULL
 * @retval	NULL
 */
void OCD_OLED_DisplayOFF(tagOLED_T *_tOLED)
{
    OLED_WR_Byte(_tOLED,0x8D,OLED_CMD);//SET DCDC����
    OLED_WR_Byte(_tOLED,0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(_tOLED,0XAE,OLED_CMD);  //DISPLAY OFF
}

/**
 * @brief 	OLED��������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	NULL
 * @retval	NULL
 */
void OCD_OLED_Clear(tagOLED_T *_tOLED)
{
    uint8_t i,n;
    for(i=0;i<8;i++)
    {	
		OLED_WR_Byte(_tOLED,0xb0+i,OLED_CMD);
		OLED_WR_Byte(_tOLED,0x00,OLED_CMD);
		OLED_WR_Byte(_tOLED,0x10,OLED_CMD);
        for(n=0;n<128;n++)  OLED_WR_Byte(_tOLED,0,OLED_DATA);
    }
}

/**
 * @brief 	OLED���ù��λ��
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x	������	x(0-127)
 * @param 	y	������	y(0-127)
 * @retval	NULL
 */
void OLED_SetCursorAddrese(tagOLED_T *_tOLED,uint8_t x,uint8_t y)
{
		OLED_WR_Byte(_tOLED,0xB0+y,OLED_CMD); 					//����ҳ��ַ
		OLED_WR_Byte(_tOLED,(x&0xF0)>>4|0x10,OLED_CMD);//�����и���ʼ��ַ(���ֽ�)
		OLED_WR_Byte(_tOLED,(x&0x0F)|0x00,OLED_CMD);   //�����е���ʼ��ַ(���ֽ�)			
}

/**
 * @brief 	OLED��ҳ��������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	page	(0-7)
 * @retval	NULL
 */
void OCD_OLED_PageClear(tagOLED_T *_tOLED,uint8_t page)
{
		uint8_t j;
		OLED_WR_Byte(_tOLED,0xB0+page,OLED_CMD); //����ҳ��ַ
		OLED_WR_Byte(_tOLED,0x10,OLED_CMD);      //�����и���ʼ��ַ(���ֽ�)
		OLED_WR_Byte(_tOLED,0x00,OLED_CMD);      //�����е���ʼ��ַ(���ֽ�)
		for(j=0;j<128;j++)
		{
				OLED_WR_Byte(_tOLED,0,OLED_DATA); //д����
		}
}

/**
 * @brief 	OLEDдһ���ַ�
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x	������	x(0-127)
 * @param 	y	������	y(0-127)
 * @param 	str	��д�ַ�
 * @param	Char_Size	��ʾ��С ��ѡ8����16
 * @retval	NULL
 */
void OLED_ShowChar(tagOLED_T *_tOLED,uint8_t x,uint8_t y,uint8_t str,uint8_t Char_Size)
{      	
	uint8_t addr=0,i=0;
	uint8_t *strflag = &str;			
	if(*strflag >= ' '&& *strflag <= '~') //��ʾӢ��
	{
		addr= *strflag-' '; //ȡģ�ӿո�ʼ�ģ������±�	
		if(Char_Size == 16)
		{
			//д8*16ASCII�ַ����ϰ벿��
			OLED_SetCursorAddrese(_tOLED,x,y); //���ù���λ��
			for(i=0;i<Char_Size/2;i++)      //����дwidth��
			{
				OLED_WR_Byte(_tOLED,ASCII_8_16[addr][i],OLED_DATA); 
			}
			//д8*16ASCII�ַ����°벿��
			OLED_SetCursorAddrese(_tOLED,x,y+1); //���ù���λ��
			for(i=0;i<Char_Size/2;i++)        //����дwidth��
			{
				OLED_WR_Byte(_tOLED,ASCII_8_16[addr][i+Char_Size/2],OLED_DATA); 
			}
			strflag++;//������ʾ��һ���ַ�	
		}
		if((Char_Size == 8))
		{
			//д6*8ASCII�ַ�
			OLED_SetCursorAddrese(_tOLED,x,y); //���ù���λ��
			for(i=0;i<6;i++)      //����дwidth��
			{
				OLED_WR_Byte(_tOLED,ASCII_6_8[addr][i],OLED_DATA); 
			}
			strflag++;//������ʾ��һ���ַ�	
		}
      
	}
}

/**
 * @brief 	OLEDд�ַ���
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x	������	x(0-127)
 * @param 	y	������	y(0-127)
 * @param 	*str	�ַ����׵�ַ��������ʾ�ַ�������
 * @param	Char_Size	��ʾ��С ��ѡ8����16
 * @retval	NULL
 */
void OCD_OLED_ShowString(tagOLED_T *_tOLED,uint8_t x,uint8_t y,uint8_t *str,uint8_t Char_Size)
{
	uint8_t i=0;
	while(str[i]!='\0') //������ʾ
	{
		OLED_ShowChar(_tOLED,x,y,str[i],Char_Size);
        if(Char_Size == 16)	//�����8*16����
		{
			x+= Char_Size/2;
			if((x+Char_Size/2) > Max_Column)  {x=0;y+=2;}	//�������
		}
		if(Char_Size == 8) //�����6*8����
		{
			x+= 6;
			if((x+6) > Max_Column)  {x=0;y+=1;}	//�������
		}
		i++;
	}
}

/**
 * @brief 	OLEDָ������
 * @param 	m	����
 * @param 	n	ָ��
 * @retval	m^n�Ľ��
 */
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t result = 1;
	while(n--)	result *= m;
	return result;
}

/**
 * @brief 	OLED��ʾ����
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x	������	x(0-127)
 * @param 	y	������	y(0-127)
 * @param 	num	����ʾ����
 * @param	len ����ʾ���ֳ���
 * @param	Char_Size	��ʾ��С ��ѡ8����16
 * @retval	NULL
 */
void OCD_OLED_ShowNum(tagOLED_T *_tOLED,uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t Char_Size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(Char_Size == 16)	OLED_ShowChar(_tOLED,x+(Char_Size/2)*t,y,' ',Char_Size);
				if(Char_Size == 8)	OLED_ShowChar(_tOLED,x+Char_Size*t,y,' ',Char_Size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	if(Char_Size == 16)	OLED_ShowChar(_tOLED,x+(Char_Size/2)*t,y,temp+'0',Char_Size);
		if(Char_Size == 8)	OLED_ShowChar(_tOLED,x+6*t,y,temp+'0',Char_Size);
	}
} 

/**
 * @brief 	OLED��ʾ������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x	������	x(0-127)
 * @param 	y	������	y(0-127)
 * @param 	Fnum	����ʾ������
 * @param	Char_Size	��ʾ��С ��ѡ8����16
 * @retval	NULL
 */
void OCD_OLED_ShowFNum(tagOLED_T *_tOLED,uint8_t x,uint8_t y,float Fnum,uint8_t Char_Size)
{
	char Data[] = "";
	sprintf(Data,"%.3f",Fnum);
	uint8_t i=0;
	while(Data[i]!='\0') //������ʾ
	{
		OLED_ShowChar(_tOLED,x,y,Data[i],Char_Size);
        if(Char_Size == 16)	//�����8*16����
		{
			x+= Char_Size/2;
			if((x+Char_Size/2) > Max_Column)  {x=0;y+=2;}	//�������
		}
		if(Char_Size == 8) //�����6*8����
		{
			x+= 6;
			if((x+6) > Max_Column)  {x=0;y+=1;}	//�������
		}
		i++;
	}
}

/**
 * @brief 	OLED��ʾBMPλͼ
 * @param   *_tOLED-OLED�ṹ��
 * @param 	x0	��ʼ������	������	x(0-127)
 * @param 	y0	��ʼ������	������	y(0-127)
 * @param	x1	��ֹ������	������	x(0-127)
 * @param	y1	��ֹ������	������	y(0-127)
 * @param 	BMP	bmp��������
 * @retval	NULL
 */
void OLED_DrawBMP(tagOLED_T *_tOLED,uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[])
{ 	
 unsigned int j=0;
 uint8_t x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetCursorAddrese(_tOLED,x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(_tOLED,BMP[j++],OLED_DATA);	    	
	    }
	}
} 

/**
 * @brief 	OLED��ʼ������
 * @param   *_tOLED-OLED�ṹ��
 * @param 	NULL
 * @retval	NULL
 */
void OCD_OLED_Init(tagOLED_T *_tOLED)
{
    Drv_IICSoft_Init(&_tOLED->tIIC);
    Drv_Delay_Ms(500);
    OLED_WR_Byte(_tOLED,0xAE,OLED_CMD); //�ر���ʾ
	OLED_WR_Byte(_tOLED,0x00,OLED_CMD);//���õ��е�ַ
	OLED_WR_Byte(_tOLED,0x10,OLED_CMD);//���ø��е�ַ
	OLED_WR_Byte(_tOLED,0x40,OLED_CMD);//������ʼ�е�ַ,��ӳ��RAM��ʾ��ʼ��(0x00~0x3F)
	OLED_WR_Byte(_tOLED,0x81,OLED_CMD);//���öԱȶȿ��ƼĴ���
	OLED_WR_Byte(_tOLED,0xCF,OLED_CMD);//����SEG�����������
	OLED_WR_Byte(_tOLED,0xA1,OLED_CMD);//���ض�������,bit0:0,0->0;1,0->127; 0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(_tOLED,0xC8,OLED_CMD);//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��   0xc0���·��� 0xc8����
	OLED_WR_Byte(_tOLED,0xA6,OLED_CMD);//����������ʾ(������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	)
	OLED_WR_Byte(_tOLED,0xA8,OLED_CMD);//��������·�� ���ö�·���ñ�(1��64)
	OLED_WR_Byte(_tOLED,0x3F,OLED_CMD);//1/64 duty(Ĭ��0X3F(1/64))
	OLED_WR_Byte(_tOLED,0xD3,OLED_CMD);//������ʾƫ��λ��ӳ��RAM������(0x00~0x3F)
	OLED_WR_Byte(_tOLED,0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(_tOLED,0xD5,OLED_CMD);//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WR_Byte(_tOLED,0x80,OLED_CMD);//���÷�Ƶ�ȣ�����ʱ��Ϊ100֡/��
	OLED_WR_Byte(_tOLED,0xD9,OLED_CMD);//����Ԥ�������
	OLED_WR_Byte(_tOLED,0xF1,OLED_CMD);//����Ԥ��15��ʱ�ӣ��ŵ�1��ʱ��([3:0],PHASE 1;[7:4],PHASE 2;)
	OLED_WR_Byte(_tOLED,0xDA,OLED_CMD);//����COMӲ����������
	OLED_WR_Byte(_tOLED,0x12,OLED_CMD);//[5:4]����
	OLED_WR_Byte(_tOLED,0xDB,OLED_CMD);//����VCOMH ��ѹ����
	OLED_WR_Byte(_tOLED,0x40,OLED_CMD);//Set VCOM �ͷŵ�ѹ([6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;)
	OLED_WR_Byte(_tOLED,0x20,OLED_CMD);//����ҳ��Ѱַģʽ(0x00/0x01/0x02)
	OLED_WR_Byte(_tOLED,0x02,OLED_CMD);//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(_tOLED,0x8D,OLED_CMD);//���ó�������/����
	OLED_WR_Byte(_tOLED,0x14,OLED_CMD);//����(0x10����,0x14����)
	OLED_WR_Byte(_tOLED,0xA4,OLED_CMD);// ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����) (0xa4/0xa5)
	OLED_WR_Byte(_tOLED,0xA6,OLED_CMD);// ������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ (0xa6/a7) 
	OLED_WR_Byte(_tOLED,0xAF,OLED_CMD);//������ʾ	
	OCD_OLED_Clear(_tOLED);
	OLED_SetCursorAddrese(_tOLED,0,0);
	//printf("OLED Init OK !\n");

}
