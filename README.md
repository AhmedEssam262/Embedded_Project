# Embedded_Project
An Embedded project using C language
#include "stdint.h"
#include "C:/Keil/Labware/inc/tm4c123gh6pm.h"


void LCD_comm(char c){                  // We are using PORTC for LED control
	
	//RS(bit-5) , RW(bit-6) , En(bit-7)
	GPIO_PORTC_DATA_R=0;
	GPIO_PORTC_DATA_R=c;
	GPIO_PORTC_DATA_R=0x80;
	
	//delay(); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	GPIO_PORTC_DATA_R=0;

	
}

void LCD_data(char d){
	
	//RS(bit-5) , RW(bit-6) , En(bit-7)
	GPIO_PORTC_DATA_R=0x20;
	GPIO_PORTC_DATA_R=d;
	GPIO_PORTC_DATA_R=0x80;
	
	//delay(); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	GPIO_PORTC_DATA_R=0;
	
}
//***************************************************************************************************************
void Init(void){

	SYSCTL_RCGCGPIO_R |= 0x24;
	while((SYSCTL_PRGPIO_R & 0x24)==0){};

	// PORTF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;

	GPIO_PORTF_DIR_R = 0xE;
	GPIO_PORTF_PUR_R = 0x11;

	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0;

	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0 ;
	//------------------------------------------------------
	// PORTC
	GPIO_PORTC_LOCK_R = 0x4C4F434B;
	GPIO_PORTC_CR_R |= 0xE0;
	
	GPIO_PORTC_DIR_R |= 0xE0;
	GPIO_PORTC_DEN_R |= 0xE0;
	GPIO_PORTC_AMSEL_R = 
	
	GPIO_PORTC_AFSEL_R = 0;
	GPIO_PORTC_PCTL_R = 0 ;



}
//***************************************************************************************************************
int main(){
	Init();
	while(1){
	if( (GPIO_PORTF_DATA_R & 0x11) == 0x01 ){
		GPIO_PORTF_DATA_R = 0x02;
	}

	else if( (GPIO_PORTF_DATA_R & 0x11)==0x10 ){
		GPIO_PORTF_DATA_R = 0x04;
	}

	else if( (GPIO_PORTF_DATA_R & 0x11)==0x00 ){
		GPIO_PORTF_DATA_R = 0x08;
	}

	else {
		GPIO_PORTF_DATA_R = 0x0E;
	}
}
	}
