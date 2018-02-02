#include "stm32f4xx.h"
#include "delay.h"

void exdddit()
{
	GPIO_InitTypeDef GPIO_InitNAME;
	EXTI_InitTypeDef EXTI_InitNAME;
	NVIC_InitTypeDef NVIC_InitTypeNAME;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);			//ʹ��SYSCFG 
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);			//ӳ���ж���
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);		//ʹ��ioE��ʱ��
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_IN;			//�ж�����IO
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitNAME.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitNAME.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitNAME);
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_OUT;		//������ʹ��IO
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitNAME.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitNAME.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitNAME);
	PEout(12)=1;
	
	EXTI_InitNAME.EXTI_Line=EXTI_Line2;			//�����ж�
	EXTI_InitNAME.EXTI_LineCmd=ENABLE;
	EXTI_InitNAME.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitNAME.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//���ش���
	EXTI_Init(&EXTI_InitNAME);
	
	NVIC_InitTypeNAME.NVIC_IRQChannel=EXTI2_IRQn;			//�ж����ȼ���������
	NVIC_InitTypeNAME.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeNAME.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeNAME.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeNAME);

}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//�ж����ȼ�����
	exdddit();
	delay_init(84);
	
  while(1);
}



void EXTI2_IRQHandler(void){
	delay_ms(200);					//������ʵ�ַ�����ʹ��λ�ķ�ת
	if(PEin(2)==0){
		PEout(12)=!PEout(12);
	}
	EXTI_ClearITPendingBit(EXTI_Line2);

}
