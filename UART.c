#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
void SystemInit () {}
	
	
	/* Assume a 16 MHZ system clock , creates 9600 baud rate */ 
void UART_Init(void)
	{		
	 SYSCTL_RCGCUART_R |= 0X0020 ;                            /* provide clock to UART5 */
	 SYSCTL_RCGCGPIO_R |= 0x0010;                             /* actviate port E */
		while((SYSCTL_PRGPIO_R&0x0010)==0){};             /*delay*/ 

		
/* UART5 Setting */  
	 UART5_CTL_R &= ~0x0001 ;                              /* disable UART */   
         UART5_IBRD_R = 0x68 ;                                /* IBRD = system clock / (16 * clock div) */ 
	 UART5_FBRD_R = 0x0B ;                                 /* FBDR = round ( 0.16667 * 64)+0.5  =  */ 
         UART5_LCRH_R = 0x0070;                                /* set 8 bits for length , FIFO enable , one stop , no parity  */
         UART5_CTL_R = 0x0301 ;                               /* enable UARTEN , TXE and RXE */



/* UART0 TX0 and RX0 use PE5 and PE4*/ 
        GPIO_PORTE_DEN_R |= 0x30;                                                           /* Make PE4 and PE5 as digital */
        GPIO_PORTE_AFSEL_R |= 0x30 ;                                                        /* Use PE4,PE5 alternate function */
	GPIO_PORTE_PCTL_R =(GPIO_PORTE_PCTL_R & 0xFF00FFFF)+0x00110000 ;                    /* configure PE4 and PE5 for UART */
	//GPIO_PORTE_PCTL_R =(GPIO_PORTE_PCTL_R & 0xFF00FFFF)|0x00110000 ;                    /* configure PE4 and PE5 for UART */

	GPIO_PORTE_AMSEL_R &= ~0x30;                                                        /* no analog for PE4 , PE5 */  
		
} 





/* Wait for New Inputs then return ASCII Code */ 
unsigned int UART_InChar(void)
{
while((UART5_FR_R&0x10) != 0){};      
return ((unsigned int)(UART5_DR_R&0xFF));
}




/* Wait for buffer to be not full then output */
void  UART_OutChar(unsigned int data)
{
while((UART5_FR_R&0x20)!= 0){};  
UART5_DR_R = data ; 
}




// switch access
void sw2_init(){
    SYSCTL_RCGCGPIO_R |= 0x20;
       while((SYSCTL_PRGPIO_R & 0x20)==0){};

       // PORTF
       GPIO_PORTF_LOCK_R = 0x4C4F434B;
       GPIO_PORTF_CR_R = 0x01;

       GPIO_PORTF_DIR_R |= 0x01;

       GPIO_PORTF_DEN_R |= 0x01;
       GPIO_PORTF_AMSEL_R = 0;

       GPIO_PORTF_AFSEL_R &= ~ 0x01;
       GPIO_PORTF_PCTL_R &= ~ 0x0000F ;
       
       GPIO_PORTF_PUR_R |= 0x01;	
	}




int main (void){} 		
		

	
