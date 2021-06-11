#include "stdint.h"
#include "GPS.h"
#include "GPS_private.h"
#include <math.h>
#include "stdio.h"

//Raw GPS Data algorithm
float calculate_distance(point x,point y){
    float delta_lat = fabs(x.lat - y.lat);
    float delta_lon = fabs(x.lon - y.lon);
    float a = pow(sin(delta_lat/2),2)+cos(x.lat)*cos(y.lat)*pow(sin(delta_lon/2),2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EARTH_RADIUS * c;
}

float degree_to_rad(double degree){
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

double string_to_double(char *data){
    char *ptr;
    ///we can also use atof()
    double number = strtod(data,&ptr);
    return number;
}
