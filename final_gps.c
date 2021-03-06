#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
void SystemInit() {}
	
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
	

	
int main()
{







}
	
