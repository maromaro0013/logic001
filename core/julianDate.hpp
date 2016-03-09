// 2014-12-30 y_ohta

#ifndef _JULIANDATE_HPP_
#define _JULIANDATE_HPP_

#include <math.h>
#include "Date.hpp"

class JulianDate : public Date {
private:
	
public:
	JulianDate() {
	}
	~JulianDate() {
	}

	double calculateJulianDayUTC() {
		double y = (double)m_year;
		double m = (double)m_month;
		double day = (double)m_day;
		if(m < 3){
			y -= 1;
			m += 12;
		}

		double hour = (double)m_hour;
		double min = (double)m_min;
		double sec = (double)m_sec;

		double a = floor((double)y / 100.0);
		double b = 2.0f - a + floor(a / 4.0);

		double julianDay = floor(365.25 * (double)(y + 4716.0)) + floor(30.6001 * (double)(m + 1.0));
		julianDay += (double)day + b - 1524.5;
		julianDay += (hour + (min + sec / 60.0 ) / 60.0 ) / 24.0;

		return julianDay;
	}

	double calculateJulianDayJST() {
		return (this->calculateJulianDayUTC() - 9.0 / 24.0);
	}

	double calculateDeltaT(double jdUTC) {
		double ye = 2000.0f + (jdUTC - 2451545.0 ) / 365.2425;

		double dt = 0.0;
		double u = 0.0;
		double t = 0.0;

		if( ye < -500 ){
			u = ( ye - 1820 ) / 100.0;
			dt = -20.0 + 32.0 * pow( u, 2 );
		}
		else if( ye < +500 ){
			u = ye / 100.0;
			double tblT[] = {10583.6, -1014.41, +33.78311, -5.952053, -0.1798452, +0.022174192, +0.0090316521};
			dt = 0.0;
			for(int i = sizeof(tblT)/sizeof(double) - 1; i >= 0; i--){
				dt = dt * u + tblT[i];
			}
		}
		else if( ye < 1600 ){
			u = ( ye - 1000.0 ) / 100.0;
			double tblT[] = {1574.2, -556.01, +71.23472, +0.319781, -0.8503463, -0.005050998, +0.0083572073};
			dt = 0.0;
			for(int i = sizeof(tblT)/sizeof(double) - 1; i >= 0; i--){
				dt = dt * u + tblT[i];
			}
		}
		else if( ye < 1700 ){
			t = ye - 1600.0;
			dt = 120.0 - 0.9808 * t - 0.01532 * pow( t, 2 ) + pow( t, 3 ) / 7129.0;
		}
		else if( ye < 1800 ){
			t = ye - 1700.0;
			dt = 8.83 + 0.1603 * t - 0.0059285 * pow( t, 2 ) + 0.00013336 * pow( t, 3 ) - pow( t, 4 ) / 1174000;
		}
		else if( ye < 1860 ){
			u = ye - 1800.0;
			double tblT[] = {13.72, -0.332447, 0.0068612, 0.0041116, -0.00037436, 0.0000121272, -0.0000001699, +0.000000000875};
			dt = 0.0;
			for(int i = sizeof(tblT)/sizeof(double) - 1; i >= 0; i--){
				dt = dt * u + tblT[i];
			}
		}
		else if( ye < 1900 ){
			u = ye - 1860.0;
			double tblT[] = {7.62, +0.5737, -0.251754, +0.01680668, -0.0004473624, 1.0 / 233174.0};
			dt = 0.0;
			for(int i = sizeof(tblT)/sizeof(double) - 1; i >= 0; i--){
				dt = dt * u + tblT[ i ];
			}
		}
		else if( ye < 1920 ){
			t = ye - 1900;
			dt = -2.79 + 1.494119 * t - 0.0598939 * pow( t, 2 ) + 0.0061966 * pow( t, 3 ) - 0.000197 * pow( t, 4 );
		}
		else if( ye < 1941 ){
			t = ye - 1920;
			dt = 21.20 + 0.84493 * t - 0.076100 * pow( t, 2 ) + 0.0020936 * pow( t, 3 );
		}
		else if( ye < 1961 ){
			t = ye - 1950.0;
			dt = 29.07 + 0.407 * t - pow( t, 2 ) / 233.0 + pow( t, 3 ) / 2547.0;
		}
		else if( ye < 1986 ){
			t = ye - 1975.0;
			dt = 45.45 + 1.067 * t - pow( t, 2 ) / 260.0 - pow( t, 3 ) / 718.0;
		}
		else if( ye < 2005 ){
			t = ye - 2000.0;
			dt = 63.86 + t * ( +0.3345 + t * ( -0.060374 + t * ( +0.0017275 + t * ( 0.000651814 + t * 0.00002373599 ) ) ) );
		}
		else if( ye < 2050 ){
			t = ye - 2000.0;
			dt = 62.92 + 0.32217 * t + 0.005589 * pow( t, 2 );
		}
		else if( ye < 2150 ){
			u = ( ye - 1820 ) / 100.0;
			dt = -20.0 + 32.0 * pow( u, 2 ) - 0.5628 * ( 2150 - ye );
		}
		else {
			u = ( ye - 1820 ) / 100.0;
			dt = -20.0 + 32.0 * pow( u, 2 );
		}
		
		return (dt / 86400.0);
	}

	double geteDeltaT(double jdUTC) {
		double myear = 2000.0 + (jdUTC - 2451545.0) / 365.2425;
		double th = (jdUTC - 2415020.0) / 36525.0;
		double t = (jdUTC - 2451545.0) / 36525.0;

		double DTS1[] = {-2.50, 228.95, 5218.61, 56282.84, 324011.78, 1061660.75, 2087298.89, 2513807.78, 1818961.41, 727058.62, 123563.95};
		double DTS2[] = {-2.44, 87.24, 815.20, -2637.80, -18756.33, 124906.15, -303191.19, 372919.88, -232424.66, 58353.42};
		double DTS3[] = {62.29, 62.97, 63.47, 63.83, 64.09, 64.30, 64.47};

		double dt = 0.0f;

		if(th < 0){
			for(int i = 10; i >= 0; i--){
				dt = dt * th + DTS1[i];
			}
		}
		else if(th < 0.97) {
			for(int i = 9; i >= 0; i--) {
				dt = dt * th + DTS2[i];
			}
		}
		else if(myear < 2004) {
			int year = (int)floor(myear);
			dt = DTS3[year - 1997];
		}
		else {
			dt = 102 * (1.0 + t) + 25.3 * t * t +0.37 * (myear - 2100);
		}
		
		return dt;
	}
};


#endif
