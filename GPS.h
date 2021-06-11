#ifndef GPS_DRIVER_GPS_H
#define GPS_DRIVER_GPS_H

#define EARTH_RADIUS 6371000
#define PI 3.14159265359

typedef struct {
    double lat;
    double lon;
}point;

double calculate_distance(point x,point y);
double degree_to_rad(double degree);
point convert_format(char *latitude, char *longitude);
void get_gps_coordinates(void);
double string_to_double(char *data);

#endif //GPS_DRIVER_GPS_H
