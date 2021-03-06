#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void LCD_Cmd(unsigned char command);
void delay_milli(int n);
void delay_micro(int n);


void SystemInit () {}



void Delay(void){
    unsigned long volatile time;
    time = 145448 * 10 ; //delay forr 1 sec
    while(time >= 1)
    {
        time-- ;
    }

}

//initialisation

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



    // PORTA For Sellectors &  PORTB to Showin output

void LCD_init(void){
        SYSCTL_RCGCGPIO_R |= 0x00; //PORTA clock
        SYSCTL_RCGCGPIO_R |= 0x01;
        SYSCTL_RCGCGPIO_R |= 0x02;
        GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS,E and R/W
        GPIO_PORTA_DEN_R |=0xE0;
        GPIO_PORTB_DIR_R |=0xFF; //PORTB D0-D7
        GPIO_PORTB_DEN_R |=0xFF; //PORTB D0-D7
        LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
        LCD_Cmd(0x06); //increments automatically
        LCD_Cmd(0x0F); //Turn on display
        LCD_Cmd(0x01); //clear display

}




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


double GPS_cordinates(double *lat_do, double *long_do, char *N_S, char *E_W)
{
    char frst_ch = '0', dumm_var = '0';   //initi.
    *lat_do = 0.0;
    *long_do = 0.0;

     //variables we will need to store the latit. and long as a strings
    char lat[20] = "0";
    char longt[20] = "0";
    bool break_for_loop =true;
    // getting the first char from gps

while(break_for_loop == true)
{
    // getting the first char from gps
    while ((UART5_FR_R & 0x10) != 0)
    {}
    frst_ch = (UART5_DR_R & 0xff);

    // check if it is the beging of nmea or not
    if(frst_ch == '$')
    {
        // check if the GPS is sending &GPGLL
    char sec_ch = '0';
    char thr_ch = '0';
    char frth_ch = '0';
    char ffth_ch = '0';
    char sx_ch = '0';     // initialise with any value

    while ((UART5_FR_R & 0x10) != 0)
           {}
           sec_ch = (UART5_DR_R & 0xff);

           while ((UART5_FR_R & 0x10) != 0)
           {}
           thr_ch = (UART5_DR_R & 0xff);

           while ((UART5_FR_R & 0x10) != 0)
           {}
           frth_ch = (UART5_DR_R & 0xff);

           while ((UART5_FR_R & 0x10) != 0)
           {}
           ffth_ch = (UART5_DR_R & 0xff);

           while ((UART5_FR_R & 0x10) != 0)
           {}
           sx_ch = (UART5_DR_R & 0xff);

    // condition to check if we in the $GPGLL
        if(sec_ch == 'G' && thr_ch == 'P' && frth_ch == 'G' && ffth_ch == 'L' && sx_ch == 'L')
        {

            // know we know that we are in the line of $GPGLL



            // we want to extract latitude and longitude.

            int comm = 0;                       //counter for ','
            bool end = true ;               // variable to check if we've ended the nmea cordinates
            // itrative loop to get the values that we need from the cordinats
            while(end == true)
                {
                    while ((UART5_FR_R & 0x10) != 0)
                    {}
                    dumm_var = (UART5_DR_R & 0xff);


                    if(comm == 1)       //getting latitude
                    {
                        if(dumm_var != ',') //condition to prevent ',' because at the end of latitude ',' will enter the outer condition
                        {
                            strncat(lat, &dumm_var, 1);
                        }
                    }

                    if(comm == 2)       //getting N/S
                    {
                        if(dumm_var != ',') //condition to prevent ',' because at the end of N/S ',' will enter the outer condition
                        {
                if(dumm_var == 'N' || dumm_var == 'S')
                {
                            *N_S = dumm_var;
                }
                        }
                    }

                    if(comm == 4)       //getting E/W
                    {
                        if(dumm_var != ',' && dumm_var != '*' ) //condition to prevent ',' because at the end of latitude ',' will enter the outer condition
                        {
                            if(dumm_var == 'E' || dumm_var == 'W')
                {
                            *E_W = dumm_var;
                }
                        }
                    }

                    if(comm == 3)           //getting longitude
                    {
                        if(dumm_var != ',')  //condition to prevent ',' because at the end of longitude ',' will enter the outer condition
                        {
                            strncat(longt, &dumm_var, 1);
                        }
                    }

                    // we will take actions depending on dumm_var
                    if(dumm_var == ',')
                    {
                        comm++ ;
                    }
                    if(dumm_var == '*')
                    {
                        end = false ;
                    }
            }

        }

    }
    if(*N_S == 'N' || *N_S == 'S')
    {
        break_for_loop = false ;
    }
}


    // converting string to double and return the values to the inputs
    *lat_do = atof(lat);
    *long_do = atof(longt);


    return 0;
}

// converting to Decmial
    //longitude


double longitudetoDecimal(double longitude ,char check){

     double minutes=0 ,seconds=0 ,result=0;
     char longitudeResult [10];
     int degrees;

     if (check == 'W'){
        degrees=longitude/-100;
     }
     else {
        degrees=longitude/100;
     }

     minutes=longitude-(double)(degrees*100);
     seconds=minutes/60.00;
     result=degrees+seconds;
     //sprintf(longitudeResult, "%f", result);
     //((double)atof(longitudeResult))
     return result;
}

    // latitude

double latitudetoDecimal(double latitude , char check){

     double minutes=0 ,seconds=0 ,result=0;
     char latitudeResult[10];
     int degrees;

     if(check == 'S'){
        degrees=latitude/-100;
     }
     else {
        degrees=latitude/100;
     }

     minutes=latitude-(double)(degrees*100);
     seconds=minutes/60.00;
     result=degrees+seconds;
    // sprintf(latitudeResult, "%f", result);
     //((double)atof(latitudeResult))
     return result;

}

// converting longitude degrees to radians

double longitudetoRadians(double longitude ,char check)
{

    longitude = longitudetoDecimal(longitude, check);
    double radian1 = (longitude *(M_PI)) / 180;
    return (radian1);
}

// converting latitude degrees to radians

double latitudetoRadians(double latitude ,char check)
{

    latitude=latitudetoDecimal(latitude, check);
    double radian2 = (latitude *(M_PI)) / 180;
    return (radian2);
}

double distance(double lat1,char check1, double long1 ,char check2,
                double lat2,char check3, double long2 ,char check4 )
{

    // Convert the latitudes and longitudes from degree to radians

    lat1  = latitudetoRadians(lat1 ,check1);
    long1 = longitudetoRadians(long1 ,check2);
    lat2  = latitudetoRadians(lat2 ,check3);
    long2 = longitudetoRadians(long2 ,check4);

    // Haversine Formula

     double dlong = long2 - long1;
     double dlat = lat2 - lat1;

     double ans = pow(sin(dlat / 2), 2)
                          + cos(lat1) * cos(lat2)
                          * pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in Kilometers, R = 6371

    double R = 6371;

    // Calculate the result
    ans = ans * R;

    return (ans*pow(10,3));
}

void led(uint32_t Distance)
{
    // Distance in Meters
    if (Distance > 100)
        {
        GPIO_PORTF_DATA_R=0x04;       // Turn on LED BLUE when the Distance exceeds 100 meters
        }


}

void LCD_Cmd(unsigned char command)
{
        GPIO_PORTA_DATA_R = 0x00; //RS =0, E=0, RW=0
        GPIO_PORTB_DATA_R =command;
        GPIO_PORTA_DATA_R =0x80; //E=1 to secure command
        delay_micro(0);
        GPIO_PORTA_DATA_R =0x00;
        if(command <4) delay_milli(2); else delay_micro(37);
}

 void LCD_Data(unsigned char data) { GPIO_PORTA_DATA_R =0x20; //RS=1, E=0,RW=0
    GPIO_PORTB_DATA_R =data;
    GPIO_PORTA_DATA_R |= 0x80;
    GPIO_PORTA_DATA_R =0x00;
    delay_micro(0);

    }
int separating_u(int final){
       int num = final;
       int u;
       u=num%10;
       return (u+48);
   }
    int separating_t(int final){
       int num = final;
       int t;
       t=(num/10)%10;
       return (t+48);
   }


    int separating_h(int final){
    int num = final;
    int h;
    h=num/100;
    return (h+48);
}

// For Delay

void delay_milli(int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<3180;j++)
    {}
  }
}

void delay_micro(int n){
    int i,j;
    for(i=0;i<n;i++){
    for(j=0;j<3;j++)
    {}
  }
}





  int main()
  {
      sw2_init();
      UART_Init();
      LED_init();
      LCD_init();

      //loop to get start point
      bool point1_xy = true;
      bool break2 = true ;
      double lat1 = 0.0;
      double long1 = 0.0;
      char N_S1 = '0';
      char E_W1 ='0';

      while (point1_xy == true)
      {

         GPS_cordinates(&lat1, &long1, &N_S1, &E_W1);
          if (lat1 != 0 && long1 != 0)
              point1_xy = false ;

      }

      //loop 2 , Tiva will be running till push button is pressed
      double lat2 = 0.0;
      double long2 = 0.0;
      double distance_acc = 0.0;
      char N_S2 = '0';
      char E_W2 = '0';
      while (break2 == true)
      {
          Delay();
         do
         {
          GPS_cordinates(&lat2 , &long2, &N_S2, &E_W2);
         }
         while(lat2 == 0 && long2 == 0);


           distance_acc +=  distance(lat1, N_S1, long1, E_W1, lat2, N_S2, long2, E_W2);

          int distance_acc_int = distance_acc;  // to reduce rounding error


          LCD_Cmd(0x01);
            LCD_Cmd(0x80);
            delay_milli(500);


            int x2= separating_h(distance_acc_int);
            LCD_Data(x2);
            delay_milli(1);

            int x1 = separating_t(distance_acc_int);
            LCD_Data(x1);
            delay_milli(1);

            int x0=separating_u(distance_acc_int);
            LCD_Data(x0);
            delay_milli(1);

            LCD_Data(' ');
            delay_milli(1);
            LCD_Data(' ');
            delay_milli(1);
            LCD_Data(' ');
            delay_milli(1);
            LCD_Data(' ');
            delay_milli(1);


            LCD_Data(' ');
            delay_milli(1);
            LCD_Data(' ');
            delay_milli(1);
            LCD_Data(' ');
            delay_milli(500);
            led(distance_acc);

            //push button
            if  ((GPIO_PORTF_DATA_R & 0x1) == 0 )
            {
            break2 = false ;
            }

            lat1 = lat2;
            long1 = long2;


       }

    }
//
