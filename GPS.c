#include "stdint.h"
#include "GPS.h"
#include <math.h>
#include "stdio.h"
#include "UART.h"
#include "stdlib.h"

extern char buf[100];
extern volatile char ind,flag,stringReceived;
char gpgga[]={'$','G','P','G','G','A'};

extern unsigned char latitude[12]; //char
extern unsigned char longitude[12];
extern unsigned char LCD_text[16];

extern unsigned char GPS_data;

//Raw GPS Data algorithm
double calculate_distance(point x,point y){
    double delta_lat, delta_lon, a, c;
    x.lat = degree_to_rad(x.lat);
    x.lon = degree_to_rad(x.lon);
    y.lat = degree_to_rad(y.lat);
    y.lon = degree_to_rad(y.lon);
    delta_lat = fabs(x.lat - y.lat);
    delta_lon = fabs(x.lon - y.lon);
    a = pow(sin(delta_lat/2),2)+cos(x.lat)*cos(y.lat)*pow(sin(delta_lon/2),2);
    c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EARTH_RADIUS * c;
}

double degree_to_rad(double degree){
    return degree * PI / 180;
}

point convert_format(char *latitude, char *longitude){
    point current;
    current.lat = string_to_double(latitude);
    current.lon = string_to_double(longitude);
    current.lat = (int)(current.lat)/100 + fmod((current.lat),100)/60;
    current.lon = (int)(current.lon)/100 + fmod((current.lon),100)/60;
    return current;
}

void get_gps_coordinates(void){
    int i;
    while(1) {
        GPS_data = UART2_read();
        buf[ind] = GPS_data;
        ind++;
        if (ind < 7) {
            if (buf[ind - 1] != gpgga[ind - 1])
                ind = 0;
        }
        ///Last character needed is 41
        if (ind >= 50) { stringReceived = 1; }

        if (stringReceived == 1) {
            ///reset indicator
            ind = 0;
            stringReceived = 0;
            for (i = 17; i < 27; i++) {
                latitude[i-17] = buf[i];
            }
            latitude[i-17] = '\0';
            for (i = 30; i < 41; i++) {
                longitude[i-30] = buf[i];
            }
            longitude[i-30] = '\0';
            return;
        }
    }
}

double string_to_double(char *data){
    char *ptr;
    ///we can also use atof()
    double number = strtod(data,&ptr);
    return number;
}
