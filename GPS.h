#ifndef GPS_DRIVER_GPS_H
#define GPS_DRIVER_GPS_H

#define EARTH_RADIUS 6371000
#define PI 3.14159265359

typedef struct {
    double lat;
    double lon;
}point;

float calculate_distance(point x,point y);
float degree_to_rad(double degree);
double string_to_double(char *data);
point convert_format(char *latitude, char *longitude);

#endif //GPS_DRIVER_GPS_H
