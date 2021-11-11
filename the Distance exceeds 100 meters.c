#include "stdint.h"
#include "tm4c123gh6pm.h" 	// Copy ("tm4c123gh6pm.h") to main file


void SystemInit(){}
void LED_init(void)
{
	SYSCTL_RCGCGPIO_R |=0X20 ;                  // enable PORT F
	while ((SYSCTL_PRGPIO_R & 0x20) == 0);      // set delay
	GPIO_PORTF_LOCK_R =0x4C4F434B;
	GPIO_PORTF_CR_R =0x04;
	GPIO_PORTF_AFSEL_R =0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R =0;
	GPIO_PORTF_DIR_R = 0x04;                // set PF2 as output
	GPIO_PORTF_DEN_R = 0x04;
	GPIO_PORTF_PUR_R = 0x11;
}
void led(uint32_t Distance)
{
    // Distance in Meters
    if (Distance > 100)
        {
        GPIO_PORTF_DATA_R=0x04;       // Turn on LED BLUE when the Distance exceeds 100 meters
        }
}
