#include "stdint.h"
#include "GPS.h"
#include "GPS_private.h"
#include <math.h>
#include "stdio.h"

float calculate_distance(point x,point y){
    float delta_lat = fabs(x.lat - y.lat);
    float delta_lon = fabs(x.lon - y.lon);
    float a = pow(sin(delta_lat/2),2)+cos(x.lat)*cos(y.lat)*pow(sin(delta_lon/2),2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EARTH_RADIUS * c;
}

//Raw GPS Data algorithm
void update_total_distance(point newPosition, point *oldPosition, float *totalDistance){
    *totalDistance += calculate_distance(newPosition,*oldPosition);
    *oldPosition = newPosition;
}

float degree_to_rad(double degree){
    return degree * PI / 180;
}

int main(void){
    point a,b;
    a.lat = degree_to_rad(30.148164306543567);
    a.lon = degree_to_rad(31.322280401201795);
    b.lat = degree_to_rad(30.148499768372297);
    b.lon = degree_to_rad(31.319695644202103);
    float distance = calculate_distance(a,b);
    for (int i = 0; i < 5; ++i) {
        update_total_distance(b,&a,&distance);
    }

    printf("%f",distance);
    return 0;
}
