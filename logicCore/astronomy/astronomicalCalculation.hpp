// 2014-11-14 y_ohta

#ifndef _ASTRONOMICALCALCULATION_HPP_
#define _ASTRONOMICALCALCULATION_HPP_

#define _USE_MATH_DEFINES
#include <math.h>
#include "../../core/julianDate.hpp"

#define deg2rad(a) ( (a) / 180.0 * M_PI )
#define rad2deg(a) ( (a) / M_PI * 180.0 )

typedef struct Nutation_t {
	double		dp;
	double		de;
}Nutation;

typedef struct Equatorial_t {
	double		RA;
	double		Dec;
}Equatorial;

typedef struct Ecliptic_t {
	double		Lon;
	double		Lat;
}Ecliptic;

class astronomyAstronomicalCalculation {
private:

public:
	astronomyAstronomicalCalculation() {
	}
	~astronomyAstronomicalCalculation() {
	}

	// get Sidereal_time
	static double calcApparentLocalSiderealTime(JulianDate &JD, double lon){
		double JDutc = JD.calculateJulianDayJST();
		double JDr = JDutc - floor(JDutc);
		double T = (JDutc - 2451545.0) / 36525.0;

		double GST = 360.0 * JDr + 0.98564736629 * (JDutc - 2451545.0);
		GST -= floor(GST / 360.0) * 360.0;
		GST += 280.46061837;
		GST += 0.000387933*T*T;
		
		double LST = GST + lon;

		double JDtdt = JDutc + JD.calculateDeltaT(JDutc);
		double obl = deg2rad(astronomyAstronomicalCalculation::calcObliquity(JDtdt));
		Nutation nutation = astronomyAstronomicalCalculation::calcNutation(JDtdt);
		double dLST = nutation.dp*cos(obl);
		
		LST += dLST / 3600.0;
		LST -= floor(LST/360.0)*360.0;
		
		return LST;
	}

	static double calcObliquity(double jdTDT){
		double T = (jdTDT - 2451545.0) / 36525.0;
		double e = 84381.448 - (46.8150 + 0.00059*T)*T;

		Nutation nutation = astronomyAstronomicalCalculation::calcNutation(jdTDT);

		return (e + nutation.de)/3600.0;
	}

	static Nutation calcNutation(double jdTDT){
		double T = (jdTDT - 2451545.0)/36525.0;
		
		double N = deg2rad(125.04452 - 1934.136261*T);
		double Ls = deg2rad(280.4665 + 36000.7698 * T);
		double Lm = deg2rad( 218.3165 + 481267.8813 * T);
		
		double dp  = -17.20*sin(N) - 1.32*sin(2.0*Ls);
		dp += -0.23*sin(2.0*Lm) + 0.21*sin(2.0*N);
		
		double de = 9.20*cos(N) + 0.57*cos(2.0*Ls);
		de += 0.10*cos(2.0*Lm) - 0.09*cos(2.0*N);

		Nutation ret;
		ret.dp = dp;
		ret.de = de;
		return ret;
	}

	/****************************************/

/*
	static Equatorial cnvEquatorial(float lon, float lat, float obl){
		
		float rLon = deg2rad(lon);
		float rLat = deg2rad(lat);
		float rObl = dqg2rad(obl);
		
		float sObl = sin(rObl);
		float cObl = cos(rObl);
		
		float Xel = cos(rLon) * cos(rLat);
		float Yel = sin(rLon) * cos(rLat);
		float Zel = sin(rLat);
		
		float Xeq = Xel;
		float Yeq = cObl * Yel - sObl * Zel;
		float Zeq = sObl * Yel + cObl * Zel;
		
		float RA = rad2deg(atan2(Yeq, Xeq));
		if(RA < 0.0) {
			RA += 360.0;
		}
		float Dec = rad2deg(asin(Zeq));

		Equatorial ret;
		ret.RA = RA;
		ret.Dec = Dec;
		return ret;
	}
*/
};

#endif

