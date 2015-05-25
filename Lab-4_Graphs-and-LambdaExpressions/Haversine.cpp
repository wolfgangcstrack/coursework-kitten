#pragma once

//#include "stdafx.h"
#include <math.h>

const double PI = 3.14159;

double Radians(double value)
{
	double radians = value * PI / 180.0;
	return radians;
}

double Haversine( double dlatitude1, double dlongitude1, double dlatitude2, double dlongitude2, double radius, double* distance )
{
    double dLatitude = Radians(dlatitude2-dlatitude1);
    double dLongitude = Radians(dlongitude2-dlongitude1);
    double nA = pow ( sin(dLatitude/2.0), 2.0 ) + cos(Radians(dlatitude1)) * cos(Radians(dlatitude2)) * pow ( sin(dLongitude/2.0), 2.0 );
    double nC = 2.0 * atan2( sqrt(nA), sqrt( 1.0 - nA ));
    *distance = radius * nC;
    return *distance; 
}
/*
void main()
{
	double sflat = 37.75;
	double sflong = 122.68;
	double nylat = 40.77;
	double nylong = 73.9;
	double radius = 6371;
	double distance;

	Haversine(sflat,sflong,nylat,nylong,radius,&distance);
	printf("Distance from SF to NY is %.2lf km",distance);
}
/*
Seattle,SEA,47.45,122.3
San Francisco,SFO,37.75,122.68
Los Angeles,LAX,33.93,118.4
Dallas/Fort Worth,DFW,32.73,96.97
Orlando,MCO,28.43,81.32
Atlanta,ATL,33.65,84.42
Salt Lake City,SLC,40.79,111.98
LaGardia,LGA,40.77,73.9
Chicago,ORD,41.98,87.9
Denver,DEN,39.75,104.87
*/

