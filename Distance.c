#include <stdint.h>
#include <iostream>
#include <math.h>


using namespace std;

// converting to Decmial
    //longitude

int degrees;
char check ;
double longitude=0 ,latitude=0 ,minutes=0 ,seconds=0 ,result=0;
char longitudeResult [10], latitudeResult[10];

double longitudetoDecimal(double longitude ,char check){

     if (check == 'W'){
        degrees=longitude/-100;
     }
     else {
        degrees=longitude/100;
     }

     minutes=longitude-(double)(degrees*100);
     seconds=minutes/60.00;
     result=degrees+seconds;
     return (result);
}

    // latitude

double latitudetoDecimal(double latitude , char check){

     if(check == 'S'){
        degrees=latitude/-100;
     }
     else {
        degrees=latitude/100;
     }

     minutes=latitude-(double)(degrees*100);
     seconds=minutes/60.00;
     result=degrees+seconds;
     return (result);

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
