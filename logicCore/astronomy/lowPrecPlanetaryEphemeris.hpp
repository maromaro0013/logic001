// 2014-11-14 y_ohta

#ifndef _LOWPRECPLANETARYEPHEMERIS_HPP_
#define _LOWPRECPLANETARYEPHEMERIS_HPP_

#define _USE_MATH_DEFINES
#include <math.h>
#include "planet.hpp"

#define deg2rad(a) ( (a) / 180.0 * M_PI )
#define rad2deg(a) ( (a) / M_PI * 180.0 )

typedef struct PlanetPosition_t {
	double						longitude;
	double						latitude;
	double						rv;			// au
}PlanetPosition;

class lowPrecPlanetaryEphemeris {
private:
	double						p1 ,p2 ,p3 ,p4 ,p5 ,p7 ,p8 ,p9 ,p10;
	double						p11, p12, p13, p14, p15, p16, p17, p18, p19, p20;
	double						p21, p22, p23, p24, p25, p26, p27, p28, p29, p30;
	double						p31, p32, p33, pt;

	double						m_longitude;
	double						m_latitude;

	int							m_sign[ePLANET_MAX];		// planet celestial longitude
	double						m_pcl[ePLANET_MAX];			// planet celestial longitude
	int							m_pcl2[ePLANET_MAX];		//
	double						m_pcb[ePLANET_MAX];			// planet celestial latitude
	int							m_pl_pos[ePLANET_MAX];		// planet position of houses

	double						m_pra[ePLANET_MAX];			//
	double						m_pdc[ePLANET_MAX];			// planet declination
	double						m_pdm[ePLANET_MAX];			// planet dairy motion
	char						m_prm[ePLANET_MAX];			// progress/retrogress mark

	int							m_casp_sign[cHOUSE_MAX];	// casp celestial longitude
	double						m_casp_pcl[cHOUSE_MAX];		// casp celestial longitude
	int							m_casp_pcl2[cHOUSE_MAX];	//

private:
	double Sind(double x) {
		return sin( deg2rad( x ) );
	}
	double Cosd(double x) {
		return cos( deg2rad( x ) );
	}

public:
	lowPrecPlanetaryEphemeris() {
		for (int i = 0; i < ePLANET_MAX; i++) {
			m_sign[i] = 0;
			m_pcl[i] = 0.0;
			m_pcl2[i] = 0;
			m_pcb[i] = 0.0;
			m_pl_pos[i] = 0;
			m_pra[i] = 0.0;
			m_pdc[i] = 0.0;
			m_pdm[i] = 0.0;
			m_prm[i] = 0;
		}
	}
	~lowPrecPlanetaryEphemeris() {
	}

	double getPlanetaryLongitude(int planet) {
		return this->m_pcl[planet];
	}
	double getPlanetaryLatitude(int planet) {
		return this->m_pcb[planet];
	}
	double getPlanetaryRightAscension(int planet) {
		return this->m_pra[planet];
	}
	double getPlanetaryDeclination(int planet) {
		return this->m_pdc[planet];
	}
	double getPlanetaryVelocity(int planet) {
		return this->m_pdm[planet];
	}
	int getPlanetarySign(int planet) {
		return this->m_sign[planet];
	}
	double getPlanetaryHouse(int planet) {
		return this->m_pl_pos[planet];
	}
	char getPlanetaryParam(int planet) {
		return this->m_prm[planet];
	}

	void calcPlanetParamaters(double jd) {
		double tt = jd - 2451545.0;
		this->pt = tt / 36525.0 + 1.0;

		this->p1 = 0.606434 + 0.03660110129 * tt;		// -mean longitude of moon

		this->p1 = (this->p1 - floor(this->p1)) * 2.0 * M_PI;
		this->p2 = 0.374897 + 0.03629164709 * tt;		// -mean anomary of moon
		this->p2 = (this->p2 - floor(this->p2)) * 2 * M_PI;
		this->p3 = 0.259091 + 0.03674819520 * tt;		// -argument of latitude of moon
		this->p3 = (this->p3 - floor(this->p3)) * 2 * M_PI;
		this->p4 = 0.827362 + 0.03386319198 * tt;		// -mean elongation of moon from sun
		this->p4 = (this->p4 - floor(this->p4)) * 2 * M_PI;
		this->p5 = 0.347343 - 0.00014709391 * tt;		// -longitude of moon ascending node
		this->p5 = (this->p5 - floor(this->p5)) * 2 * M_PI;
		this->p7 = 0.779072 + 0.00273790931 * tt;		// -mean longitude of sun
		this->p7 = (this->p7 - floor(this->p7)) * 2 * M_PI;
		this->p8 = 0.993126 + 0.00273777850 * tt;		// -mean anomary of sun
		this->p8 = (this->p8 - floor(this->p8)) * 2 * M_PI;
		this->p9 = 0.700695 + 0.01136771400 * tt;		// -mean longitude of mercury
		this->p9 = (this->p9 - floor(this->p9)) * 2 * M_PI;
		this->p10 = 0.485541 + 0.01136759566 * tt;		// -mean anomary of mercury
		this->p10 = (this->p10 - floor(this->p10)) * 2 * M_PI;
		this->p11 = 0.566441 + 0.01136762384 * tt;		// -argument of latitude of sun
		this->p11 = (this->p11 - floor(this->p11)) * 2 * M_PI;
		this->p12 = 0.505498 + 0.00445046867 * tt;		// -mean longitude of venus
		this->p12 = (this->p12 - floor(this->p12)) * 2 * M_PI;
		this->p13 = 0.140023 + 0.00445036173 * tt;		// -mean anomary of venus
		this->p13 = (this->p13 - floor(this->p13)) * 2 * M_PI;
		this->p14 = 0.292498 + 0.00445040017 * tt;		// -argument of latitude of venus
		this->p14 = (this->p14 - floor(this->p14)) * 2 * M_PI;
		this->p15 = 0.987353 + 0.00145575328 * tt;		// -mean longitude of mars
		this->p15 = (this->p15 - floor(this->p15)) * 2 * M_PI;
		this->p16 = 0.053856 + 0.00145561327 * tt;		// -mean anomary of mars
		this->p16 = (this->p16 - floor(this->p16)) * 2 * M_PI;
		this->p17 = 0.849694 + 0.00145569465 * tt;		// -argument of latitude of mars
		this->p17 = (this->p17 - floor(this->p17)) * 2 * M_PI;
		this->p18 = 0.089608 + 0.00023080893 * tt;		// -mean longitude of jupiter
		this->p18 = (this->p18 - floor(this->p18)) * 2 * M_PI;
		this->p19 = 0.056531 + 0.00023080893 * tt;		// -mean anomary of jupiter
		this->p19 = (this->p19 - floor(this->p19)) * 2 * M_PI;
		this->p20 = 0.814794 + 0.00023080893 * tt;		// -argument of latitude of jupiter
		this->p20 = (this->p20 - floor(this->p20)) * 2 * M_PI;
		this->p21 = 0.133295 + 0.00009294371 * tt;		// -mean longitude of saturn
		this->p21 = (this->p21 - floor(this->p21)) * 2 * M_PI;
		this->p22 = 0.882987 + 0.00009294371 * tt;		// -mean anomary of saturn
		this->p22 = (this->p22 - floor(this->p22)) * 2 * M_PI;
		this->p23 = 0.821218 + 0.00009294371 * tt;		// -argument of latitude of saturn
		this->p23 = (this->p23 - floor(this->p23)) * 2 * M_PI;
		this->p24 = 0.870169 + 0.00003269438 * tt;		// -mean longitude of uranus
		this->p24 = (this->p24 - floor(this->p24)) * 2 * M_PI;
		this->p25 = 0.400589 + 0.00003269438 * tt;		// -mean anomary of uranus
		this->p25 = (this->p25 - floor(this->p25)) * 2 * M_PI;
		this->p26 = 0.664614 + 0.00003265562 * tt;		// -argument of latitude of uranus
		this->p26 = (this->p26 - floor(this->p26)) * 2 * M_PI;
		this->p27 = 0.846912 + 0.00001672092 * tt;		// -mean longitude of neptune
		this->p27 = (this->p27 - floor(this->p27)) * 2 * M_PI;
		this->p28 = 0.725368 + 0.00001672092 * tt;		// -mean anomary of neptune
		this->p28 = (this->p28 - floor(this->p28)) * 2 * M_PI;
		this->p29 = 0.480856 + 0.00001663715 * tt;		// -argument of latitude of neptune
		this->p29 = (this->p29 - floor(this->p29)) * 2 * M_PI;
		this->p31 = 0.663854 + 0.00001115482 * tt;		// -mean longitude of pluto
		this->p31 = (this->p31 - floor(this->p31)) * 2 * M_PI;
		this->p32 = 0.041020 + 0.00001104864 * tt;		// -mean anomary of pluto
		this->p32 = (this->p32 - floor(this->p32)) * 2 * M_PI;
		this->p33 = 0.357355 + 0.00001104864 * tt;		// -argument of latitude of pluto
		this->p33 = (this->p33 - floor(this->p33)) * 2 * M_PI;

//		this->p99 = (1934 * this->pt - 1789) / 360;
//		this->p99 = (this->p99 - floor(this->p99)) * 2 * M_PI;
	}

/*	#************************************#
	# sun position caliculate sub 1      #
	#   (geocentric ecliptic)            #
	#  output : cl = longitude [sec,deg] #
	#           cb = latitude  [sec,deg] #
	#           rv = radius    [AU]      #
	#************************************# */
	PlanetPosition Sun_cal1(void) {
		double cl = 1296000 * this->p7 / M_PI / 2;
		cl +=   6910 * sin(this->p8);
		cl +=     72 * sin(2 * this->p8);
		cl -=     17 * this->pt * sin(this->p8);
		cl -=      7 * cos(this->p8 - this->p19);
		cl +=      6 * sin(this->p1 - this->p7);
		cl +=      5 * sin(4 * this->p8 - 8 * this->p16 + 3 * this->p19);
		cl -=      5 * cos(2 * this->p8 - 2 * this->p13);
		cl -=      4 * sin(this->p8 - this->p13);
		cl +=      4 * cos(4 * this->p8 - 8 * this->p16 + 3 * this->p19);
		cl +=      3 * sin(2 * this->p8 - 2 * this->p13);
		cl -=      3 * sin(this->p19);
		cl -=      3 * sin(2 * this->p8 - 2 * this->p19);
		
		double cb = 0;
		
		double rv = 1.00014;
		rv -= 0.01675 * cos(this->p8);
		rv -= 0.00014 * cos(2 * this->p8);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#*************************#
	# moon position cal sub 1 #
	#   (geocentric ecliptic) #
	#*************************# */
	PlanetPosition Moon_cal1() {
		double cl = 1296000 * this->p1 / M_PI / 2;
		cl +=  22640 * sin(this->p2);
		cl -=   4586 * sin(this->p2 - 2 * this->p4);
		cl +=   2370 * sin(2 * this->p4);
		cl +=    769 * sin(2 * this->p2);
		cl -=    668 * sin(this->p8);
		cl -=    412 * sin(2 * this->p3);
		cl -=    212 * sin(2 * this->p2 - 2 * this->p4);
		cl -=    206 * sin(this->p2 - 2 * this->p4 + this->p8);
		cl +=    192 * sin(this->p2 + 2 * this->p4);
		cl +=    165 * sin(2 * this->p4 - this->p8);
		cl +=    148 * sin(this->p2 - this->p8);
		cl -=    125 * sin(this->p4);
		cl -=    110 * sin(this->p2 + this->p8);
		cl -=     55 * sin(2 * this->p3-2 * this->p4);
		cl -=     45 * sin(this->p2 + 2 * this->p3);
		cl +=     40 * sin(this->p2 - 2 * this->p3);
		cl -=     38 * sin(this->p2 - 4 * this->p4);
		cl +=     36 * sin(3 * this->p2);
		cl -=     31 * sin(2 * this->p2 - 4 * this->p4);
		cl +=     28 * sin(this->p2 - 2 * this->p4 - this->p8);
		cl -=     24 * sin(2 * this->p4 + this->p8);
		cl +=     19 * sin(this->p2 - this->p4);
		cl +=     18 * sin(this->p4 + this->p8);
		cl +=     15 * sin(this->p2 + 2 * this->p4 - this->p8);
		cl +=     14 * sin(2 * this->p2 + 2 * this->p4);
		cl +=     14 * sin(4 * this->p4);
		cl -=     13 * sin(3 * this->p2 - 2 * this->p4);
		cl -=     11 * sin(this->p2 + 16 * this->p7 - 18 * this->p12);
		cl +=     10 * sin(2 * this->p2 - this->p8);
		cl +=      9 * sin(this->p2 - 2 * this->p3 - 2 * this->p4);
		cl +=      9 * cos(this->p2 + 16 * this->p7 - 18 * this->p12);
		cl -=      9 * sin(2 * this->p2 - 2 * this->p4 + this->p8);
		cl -=      8 * sin(this->p2 + this->p4);
		cl +=      8 * sin(2 * this->p4 - 2 * this->p8);
		cl -=      8 * sin(2 * this->p2 + this->p8);
		cl -=      7 * sin(2 * this->p8);
		cl -=      7 * sin(this->p2 - 2 * this->p4+2 * this->p8);
		cl +=      7 * sin(this->p5);
		cl -=      6 * sin(this->p2 - 2 * this->p3 + 2 * this->p4);
		cl -=      6 * sin(2 * this->p3 + 2 * this->p4);
		cl -=      4 * sin(this->p2 - 4 * this->p4 + this->p8);
		cl +=      4 * this->pt * cos(this->p2 + 16 * this->p7 - 18 * this->p12);
		cl -=      4 * sin(2 * this->p2 + 2 * this->p3);
		cl +=      4 * this->pt * sin(this->p2 + 16 * this->p7 - 18 * this->p12);
		cl +=      3 * sin(this->p2 - 3 * this->p4);
		cl -=      3 * sin(this->p2 + 2 * this->p4 + this->p8);
		cl -=      3 * sin(2 * this->p2 - 4 * this->p4 + this->p8);
		cl +=      3 * sin(this->p2 - 2 * this->p8);
		cl +=      3 * sin(this->p2 - 2 * this->p4 - 2 * this->p8);
		cl -=      2 * sin(2 * this->p2 - 2 * this->p4 - this->p8);
		cl -=      2 * sin(2 * this->p3 - 2 * this->p4 + this->p8);
		cl +=      2 * sin(this->p2 + 4 * this->p4);
		cl +=      2 * sin(4 * this->p2);
		cl +=      2 * sin(4 * this->p4 - this->p8);
		cl +=      2 * sin(2 * this->p2 - this->p4);
		
		double cb = 18461 * sin(this->p3);
		cb += 1010 * sin(this->p2 + this->p3);
		cb += 1000 * sin(this->p2 - this->p3);
		cb -=  624 * sin(this->p3 - 2 * this->p4);
		cb -=  199 * sin(this->p2 - this->p3 - 2 * this->p4);
		cb -=  167 * sin(this->p2 + this->p3 - 2 * this->p4);
		cb +=  117 * sin(this->p3 + 2 * this->p4);
		cb +=   62 * sin(2 * this->p2 + this->p3);
		cb +=   33 * sin(this->p2 - this->p3 + 2 * this->p4);
		cb +=   32 * sin(2 * this->p2 - this->p3);
		cb -=   30 * sin(this->p3 - 2 * this->p4 + this->p8);
		cb -=   16 * sin(2 * this->p2 + this->p3 - 2 * this->p4);
		cb +=   15 * sin(this->p2 + this->p3 + 2 * this->p4);
		cb +=   12 * sin(this->p3 - 2 * this->p4 - this->p8);
		cb -=    9 * sin(this->p2 - this->p3 - 2 * this->p4 + this->p8);
		cb -=    8 * sin(this->p3 + this->p5);
		cb +=    8 * sin(this->p3 + 2 * this->p4 - this->p8);
		cb -=    7 * sin(this->p2 + this->p3 - 2 * this->p4 + this->p8);
		cb +=    7 * sin(this->p2 + this->p3 - this->p8);
		cb -=    7 * sin(this->p2 + this->p3 - 4 * this->p4);
		cb -=    6 * sin(this->p3 + this->p8);
		cb -=    6 * sin(3 * this->p3);
		cb +=    6 * sin(this->p2 - this->p3 - this->p8);
		cb -=    5 * sin(this->p3 + this->p4);
		cb -=    5 * sin(this->p2 + this->p3 + this->p8);
		cb -=    5 * sin(this->p2 - this->p3 + this->p8);
		cb +=    5 * sin(this->p3 - this->p8);
		cb +=    5 * sin(this->p3 - this->p4);
		cb +=    4 * sin(3 * this->p2 + this->p3);
		cb -=    4 * sin(this->p3 - 4 * this->p4);
		cb -=    3 * sin(this->p2 - this->p3 - 4 * this->p4);
		cb +=    3 * sin(this->p2 - 3 * this->p3);
		cb -=    2 * sin(2 * this->p2 - this->p3 - 4 * this->p4);
		cb -=    2 * sin(3 * this->p3 - 2 * this->p4);
		cb +=    2 * sin(2 * this->p2 - this->p3 + 2 * this->p4);
		cb +=    2 * sin(this->p2 - this->p3 + 2 * this->p4 - this->p8);
		cb +=    2 * sin(2 * this->p2 - this->p3 - 2 * this->p4);
		cb +=    2 * sin(3 * this->p2 - this->p3);
		
		PlanetPosition ret = {cl, cb, 0.0};
		return ret;
	}

/*	#****************************#
	# mercury position cal sub 1 #
	#   (heriocentric ecliptic)  #
	#****************************# */
	PlanetPosition Mercury_cal1() {
		double cl = 1296000.0 * this->p9 / M_PI / 2.0;
		cl +=  84378.0 * sin(this->p10);
		cl +=  10733.0 * sin(2.0 * this->p10);
		cl +=   1892.0 * sin(3.0 * this->p10);
		cl -=    646.0 * sin(2.0 * this->p11);
		cl +=    381.0 * sin(4.0 * this->p10);
		cl -=    306.0 * sin(this->p10 - 2.0 * this->p11);
		cl -=    274.0 * sin(this->p10 + 2.0 * this->p11);
		cl -=     92.0 * sin(2.0 * this->p10 + 2.0 * this->p11);
		cl +=     83.0 * sin(5.0 * this->p10);
		cl -=     28.0 * sin(3.0 * this->p10 + 2.0 * this->p11);
		cl +=     25.0 * sin(2.0 * this->p10 - 2.0 * this->p11);
		cl +=     19.0 * sin(6.0 * this->p10);
		cl -=      9.0 * sin(4.0 * this->p10 + 2.0 * this->p11);
		cl +=      8.0 * this->pt * sin(this->p10);
		cl +=      7.0 * cos(2.0 * this->p10 - 5.0 * this->p13);
		
		double cb = 24134.0 * sin(this->p11);
		cb += 5180.0 * sin(this->p10 - this->p11);
		cb += 4910.0 * sin(this->p10 + this->p11);
		cb += 1124.0 * sin(2 * this->p10 + this->p11);
		cb +=  271.0 * sin(3 * this->p10 + this->p11);
		cb +=  132.0 * sin(2 * this->p10 - this->p11);
		cb +=   67.0 * sin(4 * this->p10 + this->p11);
		cb +=   18.0 * sin(3 * this->p10 - this->p11);
		cb +=   17.0 * sin(5 * this->p10 + this->p11);
		cb -=   10.0 * sin(3 * this->p11);
		cb -=    9.0 * sin(this->p10 - 3 * this->p11);
		
		double rv = 0.39528;
		rv -= 0.07834 * cos(this->p10);
		rv -= 0.00795 * cos(2 * this->p10);
		rv -= 0.00121 * cos(3 * this->p10);
		rv -= 0.00022 * cos(4 * this->p10);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#**************************#
	# venus position cal sub 1 #
	#**************************# */
	PlanetPosition Venus_cal1() {
		double cl = 1296000 * this->p12 / M_PI / 2;
		cl +=   2814 * sin(this->p13);
		cl -=    181 * sin(2 * this->p14);
		cl -=     20 * this->pt * sin(this->p13);
		cl +=     12 * sin(2 * this->p13);
		cl -=     10 * cos(2 * this->p8 - 2 * this->p13);
		cl +=      7 * cos(3 * this->p8 - 3 * this->p13);
		
		double cb = 12215 * sin(this->p14);
		cb +=   83 * sin(this->p13 + this->p14);
		cb +=   83 * sin(this->p13 - this->p14);
		
		double rv = 0.72335;
		rv -=0.00493 * cos(this->p13);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#*************************#
	# mars position cal sub 1 #
	#*************************# */
	PlanetPosition Mars_cal1() {
		double cl = 1296000 * this->p15 / M_PI / 2;
		cl +=  38451 * sin(this->p16);
		cl +=   2238 * sin(2 * this->p16);
		cl +=    181 * sin(3 * this->p16);
		cl -=     52 * sin(2 * this->p17);
		cl +=     37 * this->pt * sin(this->p16);
		cl -=     22 * cos(this->p16 - 2 * this->p19);
		cl -=     19 * sin(this->p16 - this->p19);
		cl +=     17 * cos(this->p16 - this->p19);
		cl +=     17 * sin(4 * this->p16);
		cl -=     16 * cos(2 * this->p16 - 2 * this->p19);
		cl +=     13 * cos(this->p8 - 2 * this->p16);
		cl -=     10 * sin(this->p16 - 2 * this->p17);
		cl -=     10 * sin(this->p16 + 2 * this->p17);
		cl +=      7 * cos(this->p8 - this->p16);
		cl -=      7 * cos(2 * this->p8 - 3 * this->p16);
		cl -=      5 * sin(this->p13 - 3 * this->p16);
		cl -=      5 * sin(this->p8 - this->p16);
		cl -=      5 * sin(this->p8 - 2 * this->p16);
		cl -=      4 * cos(2 * this->p8 - 4 * this->p16);
		cl +=      4 * this->pt * sin(2 * this->p16);
		cl +=      4 * cos(this->p19);
		cl +=      3 * cos(this->p13 - 3 * this->p16);
		cl +=      3 * sin(2 * this->p16 - 2 * this->p19);
		
		double cb = 6603 * sin(this->p17);
		cb += 622 * sin(this->p16 - this->p17);
		cb += 615 * sin(this->p16 + this->p17);
		cb +=  64 * sin(2 * this->p16 + this->p17);
		
		double rv = 1.53031;
		rv -= 0.14170 * cos(this->p16);
		rv -= 0.00660 * cos(2*this->p16);
		rv -= 0.00047 * cos(3*this->p16);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#****************************#
	# jupiter position cal sub 1 #
	#****************************# */
	PlanetPosition Jupiter_cal1() {
		double cl = 1296000 * this->p18 / M_PI / 2;
		cl +=  19934 * sin(this->p19);
		cl +=   5023 * this->pt;
		cl +=   2511;
		cl +=   1093 * cos(2 * this->p19 - 5 * this->p22);
		cl +=    601 * sin(2 * this->p19);
		cl -=    479 * sin(2 * this->p19 - 5 * this->p22);
		cl -=    185 * sin(2 * this->p19 - 2 * this->p22);
		cl +=    137 * sin(3 * this->p19 - 5 * this->p22);
		cl -=    131 * sin(this->p19 - 2 * this->p22);
		cl +=     79 * cos(this->p19 - this->p22);
		cl -=     76 * cos(2 * this->p19 - 2 * this->p22);
		cl -=     74 * this->pt * cos(this->p19);
		cl +=     68 * this->pt * sin(this->p19);
		cl +=     66 * cos(2 * this->p19 - 3 * this->p22);
		cl +=     63 * cos(3 * this->p19 - 5 * this->p22);
		cl +=     53 * cos(this->p19 - 5 * this->p22);
		cl +=     49 * sin(2 * this->p19 - 3 * this->p22);
		cl -=     43 * this->pt * sin(2 * this->p19 - 5 * this->p22);
		cl -=     37 * cos(this->p19);
		cl +=     25 * sin(2 * this->p18);
		cl +=     25 * sin(3 * this->p19);
		cl -=     23 * sin(this->p19 - 5 * this->p22);
		cl -=     19 * this->pt * cos(2 * this->p19 - 5 * this->p22);
		cl +=     17 * cos(2 * this->p19 - 4 * this->p22);
		cl +=     17 * cos(3 * this->p19 - 3 * this->p22);
		cl -=     14 * sin(this->p19 - this->p22);
		cl -=     13 * sin(3 * this->p19 - 4 * this->p22);
		cl -=      9 * cos(2 * this->p18);
		cl +=      9 * cos(this->p22);
		cl -=      9 * sin(this->p22);
		cl -=      9 * sin(3 * this->p19 - 2 * this->p22);
		cl +=      9 * sin(4 * this->p19 - 5 * this->p22);
		cl +=      9 * sin(2 * this->p19 - 6 * this->p22 + 3 * this->p25);
		cl -=      8 * cos(4 * this->p19 - 10 * this->p22);
		cl +=      7 * cos(3 * this->p19 - 4 * this->p22);
		cl -=      7 * cos(this->p19 - 3 * this->p22);
		cl -=      7 * sin(4 * this->p19 - 10 * this->p22);
		cl -=      7 * sin(this->p19 - 3 * this->p22);
		cl +=      6 * cos(4 * this->p19 - 5 * this->p22);
		cl -=      6 * sin(3 * this->p19 - 3 * this->p22);
		cl +=      5 * cos(2 * this->p22);
		cl -=      4 * sin(4 * this->p19 - 4 * this->p22);
		cl -=      4 * cos(3 * this->p22);
		cl +=      4 * cos(2 * this->p19 - this->p22);
		cl -=      4 * cos(3 * this->p19 - 2 * this->p22);
		cl -=      4 * this->pt * cos(2 * this->p19);
		cl +=      3 * this->pt * sin(2 * this->p19);
		cl +=      3 * cos(5 * this->p22);
		cl +=      3 * cos(5 * this->p19 - 10 * this->p22);
		cl +=      3 * sin(2 * this->p22);
		cl -=      2 * sin(2 * this->p18 - this->p19);
		cl +=      2 * sin(2 * this->p18 + this->p19);
		cl -=      2 * this->pt * sin(3 * this->p19 - 5 * this->p22);
		cl -=      2 * this->pt * sin(this->p19 - 5 * this->p22);
		
		double cb = -4692 * cos(this->p19);
		cb +=  259 * sin(this->p19);
		cb +=  227;
		cb -=  227 * cos(2 * this->p19);
		cb +=   30 * this->pt * sin(this->p19);
		cb +=   21 * this->pt * cos(this->p19);
		cb +=   16 * sin(3 * this->p19 - 5 * this->p22);
		cb -=   13 * sin(this->p19 - 5 * this->p22);
		cb -=   12 * cos(3 * this->p19);
		cb +=   12 * sin(2 * this->p19);
		cb +=    7 * cos(3 * this->p19 - 5 * this->p22);
		cb -=    5 * cos(this->p19 - 5 * this->p22);
		
		double rv = 5.20883;
		rv -=0.25122 * cos(this->p19);
		rv -=0.00604 * cos(2 * this->p19);
		rv +=0.00260 * cos(2 * this->p19 - 2 * this->p22);
		rv -=0.00170 * cos(3 * this->p19 - 5 * this->p22);
		rv -=0.00106 * sin(2 * this->p19 - 2 * this->p22);
		rv -=0.00091 * this->pt * sin(this->p19);
		rv -=0.00084 * this->pt * cos(this->p19);
		rv +=0.00069 * sin(2 * this->p19 - 3 * this->p22);
		rv -=0.00067 * sin(this->p19 - 5 * this->p22);
		rv +=0.00066 * sin(3 * this->p19 - 5 * this->p22);
		rv +=0.00063 * sin(this->p19 - this->p22);
		rv -=0.00051 * cos(2 * this->p19 - 3 * this->p22);
		rv -=0.00046 * sin(this->p19);
		rv -=0.00029 * cos(this->p19 - 5 * this->p22);
		rv +=0.00027 * cos(this->p19 - 2 * this->p22);
		rv -=0.00022 * cos(3 * this->p19);
		rv -=0.00021 * sin(2 * this->p19 - 5 * this->p22);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#***************************#
	# saturn position cal sub 1 #
	#***************************# */
	PlanetPosition Saturn_cal1() {
		double cl = 1296000 * this->p21 / M_PI / 2;
		cl +=  23045 * sin(this->p22);
		cl +=   5014 * this->pt;
		cl -=   2689 * cos(2 * this->p19 - 5 * this->p22);
		cl +=   2507;
		cl +=   1177 * sin(2 * this->p19 - 5 * this->p22);
		cl -=    826 * cos(2 * this->p19 - 4 * this->p22);
		cl +=    802 * sin(2 * this->p22);
		cl +=    425 * sin(this->p19 - 2 * this->p22);
		cl -=    229 * this->pt * cos(this->p22);
		cl -=    153 * cos(2 * this->p19 - 6 * this->p22);
		cl -=    142 * this->pt * sin(this->p22);
		cl -=    114 * cos(this->p22);
		cl +=    101 * this->pt * sin(2 * this->p19 - 5 * this->p22);
		cl -=     70 * cos(2 * this->p21);
		cl +=     67 * sin(2 * this->p21);
		cl +=     66 * sin(2 * this->p19 - 6 * this->p22);
		cl +=     60 * this->pt * cos(2 * this->p19 - 5 * this->p22);
		cl +=     41 * sin(this->p19 - 3 * this->p22);
		cl +=     39 * sin(3 * this->p22);
		cl +=     31 * sin(this->p19 - this->p22);
		cl +=     31 * sin(2 * this->p19 - 2 * this->p22);
		cl -=     29 * cos(2 * this->p19 - 3 * this->p22);
		cl -=     28 * sin(2 * this->p19 - 6 * this->p22 + 3 * this->p25);
		cl +=     28 * cos(this->p19 - 3 * this->p22);
		cl +=     22 * this->pt * sin(2 * this->p19 - 4 * this->p22);
		cl -=     22 * sin(this->p22 - 3 * this->p25);
		cl +=     20 * sin(2 * this->p19 - 3 * this->p22);
		cl +=     20 * cos(4 * this->p19 - 10 * this->p22);
		cl +=     19 * cos(2 * this->p22 - 3 * this->p25);
		cl +=     19 * sin(4 * this->p19 - 10 * this->p22);
		cl -=     17 * this->pt * cos(2 * this->p22);
		cl -=     16 * cos(this->p22 - 3 * this->p25);
		cl -=     12 * sin(2 * this->p19 - 4 * this->p22);
		cl +=     12 * cos(this->p19);
		cl -=     12 * sin(2 * this->p22 - 2 * this->p25);
		cl -=     11 * this->pt * sin(2 * this->p22);
		cl -=     11 * cos(2 * this->p19 - 7 * this->p22);
		cl +=     10 * sin(2 * this->p22 - 3 * this->p25);
		cl +=     10 * cos(2 * this->p19 - 2 * this->p22);
		cl +=      9 * sin(4 * this->p19 - 9 * this->p22);
		cl -=      8 * sin(this->p22 - 2 * this->p25);
		cl -=      8 * cos(2 * this->p21 + this->p22);
		cl +=      8 * cos(2 * this->p21 - this->p22);
		cl +=      8 * cos(this->p22 - this->p25);
		cl -=      8 * sin(2 * this->p21 - this->p22);
		cl +=      7 * sin(2 * this->p21 + this->p22);
		cl -=      7 * cos(this->p19 - 2 * this->p22);
		cl -=      7 * cos(2 * this->p22);
		cl -=      6 * this->pt * sin(4 * this->p19 - 10 * this->p22);
		cl +=      6 * this->pt * cos(4 * this->p19 - 10 * this->p22);
		cl +=      6 * this->pt * sin(2 * this->p19 - 6 * this->p22);
		cl -=      5 * sin(3 * this->p19 - 7 * this->p22);
		cl -=      5 * cos(3 * this->p19 - 3 * this->p22);
		cl -=      5 * cos(2 * this->p22 - 2 * this->p25);
		cl +=      5 * sin(3 * this->p19 - 4 * this->p22);
		cl +=      5 * sin(2 * this->p19 - 7 * this->p22);
		cl +=      4 * sin(3 * this->p19 - 3 * this->p22);
		cl +=      4 * sin(3 * this->p19 - 5 * this->p22);
		cl +=      4 * this->pt * cos(this->p19 - 2 * this->p22);
		cl +=      3 * this->pt * cos(2 * this->p19 - 4 * this->p22);
		cl +=      3 * cos(2 * this->p19 - 6 * this->p22 + 3 * this->p25);
		cl -=      3 * this->pt * sin(2 * this->p21);
		cl +=      3 * this->pt * cos(2 * this->p19 - 6 * this->p22);
		cl -=      3 * this->pt * cos(2 * this->p21);
		cl +=      3 * cos(3 * this->p19 - 7 * this->p22);
		cl +=      3 * cos(4 * this->p19 - 9 * this->p22);
		cl +=      3 * sin(3 * this->p19 - 6 * this->p22);
		cl +=      3 * sin(2 * this->p19 - this->p22);
		cl +=      3 * sin(this->p19 - 4 * this->p22);
		cl +=      2 * cos(3 * this->p22 - 3 * this->p25);
		cl +=      2 * this->pt * sin(this->p19 - 2 * this->p22);
		cl +=      2 * sin(4 * this->p22);
		cl -=      2 * cos(3 * this->p19 - 4 * this->p22);
		cl -=      2 * cos(2 * this->p19 - this->p22);
		cl -=      2 * sin(2 * this->p19 - 7 * this->p22 + 3 * this->p25);
		cl +=      2 * cos(this->p19 - 4 * this->p22);
		cl +=      2 * cos(4 * this->p19 - 11 * this->p22);
		cl -=      2 * sin(this->p22 - this->p25);
		
		double cb = 8297 * sin(this->p22);
		cb -=3346 * cos(this->p22);
		cb += 462 * sin(2*this->p22);
		cb -= 189 * cos(2*this->p22);
		cb += 185;
		cb +=  79 * this->pt * cos(this->p22);
		cb -=  71 * cos(2 * this->p19 - 4 * this->p22);
		cb +=  46 * sin(2 * this->p19 - 6 * this->p22);
		cb -=  45 * cos(2 * this->p19 - 6 * this->p22);
		cb +=  29 * sin(3 * this->p22);
		cb -=  20 * cos(2 * this->p19 - 3 * this->p22);
		cb +=  18 * this->pt * sin(this->p22);
		cb -=  14 * cos(2 * this->p19 - 5 * this->p22);
		cb -=  11 * cos(3 * this->p22);
		cb -=  10 * this->pt;
		cb +=   9 * sin(this->p19 - 3 * this->p22);
		cb +=   8 * sin(this->p19 - this->p22);
		cb -=   6 * sin(2 * this->p19 - 3 * this->p22);
		cb +=   5 * sin(2 * this->p19 - 7 * this->p22);
		cb -=   5 * cos(2 * this->p19 - 7 * this->p22);
		cb +=   4 * sin(2 * this->p19 - 5 * this->p22);
		cb -=   4 * this->pt * sin(2 * this->p22);
		cb -=   3 * cos(this->p19 - this->p22);
		cb +=   3 * cos(this->p19 - 3 * this->p22);
		cb +=   3 * this->pt * sin(2 * this->p19 - 4 * this->p22);
		cb +=   3 * sin(this->p19 - 2 * this->p22);
		cb +=   2 * sin(4 * this->p22);
		cb -=   2 * cos(2 * this->p19 - 2 * this->p22);
		
		double rv = 9.55774;
		rv -= 0.53252 * cos(this->p22);
		rv -= 0.01878 * sin(2 * this->p19 - 4 * this->p22);
		rv -= 0.01482 * cos(2 * this->p22);
		rv += 0.00817 * sin(this->p19 - this->p22);
		rv -= 0.00539 * cos(this->p19 - 2 * this->p22);
		rv -= 0.00524 * this->pt * sin(this->p22);
		rv += 0.00349 * sin(2 * this->p19 - 5 * this->p22);
		rv += 0.00347 * sin(2 * this->p19 - 6 * this->p22);
		rv += 0.00328 * this->pt * cos(this->p22);
		rv -= 0.00225 * sin(this->p22);
		rv += 0.00149 * cos(2 * this->p19 - 6 * this->p22);
		rv -= 0.00126 * cos(2 * this->p19 - 2 * this->p22);
		rv += 0.00104 * cos(this->p19 - this->p22);
		rv += 0.00101 * cos(2 * this->p19 - 5 * this->p22);
		rv += 0.00098 * cos(this->p19 - 3 * this->p22);
		rv -= 0.00073 * cos(2 * this->p19 - 3 * this->p22);
		rv -= 0.00062 * cos(3 * this->p22);
		rv += 0.00042 * sin(2 * this->p22 - 3 * this->p25);
		rv += 0.00041 * sin(2 * this->p19 - 2 * this->p22);
		rv -= 0.00040 * sin(this->p19 - 3 * this->p22);
		rv += 0.00040 * cos(2 * this->p19 - 4 * this->p22);
		rv -= 0.00028 * this->pt;
		rv -= 0.00023 * sin(this->p19);
		rv += 0.00020 * sin(2 * this->p19 - 7 * this->p22);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#***************************#
	# uranus position cal sub 1 #
	#***************************#	*/

	PlanetPosition Uranus_cal1() {
		double cl = 1296000 * this->p24 / M_PI / 2;
		cl +=  19397 * sin(this->p25);
		cl +=    570 * sin(2 * this->p25);
		cl -=    536 * this->pt * cos(this->p25);
		cl +=    143 * sin(this->p22 - 2 * this->p25);
		cl +=    110 * this->pt * sin(this->p25);
		cl +=    102 * sin(this->p22 - 3 * this->p25);
		cl +=     76 * cos(this->p22 - 3 * this->p25);
		cl -=     49 * sin(this->p19 - this->p25);
		cl +=     32 * this->pt * this->pt;
		cl -=     30 * this->pt * cos(2 * this->p25);
		cl +=     29 * sin(2 * this->p19 - 6 * this->p22 + 3 * this->p25);
		cl +=     29 * cos(2 * this->p25 - 2 * this->p28);
		cl -=     28 * cos(this->p25 - this->p28);
		cl +=     23 * sin(3 * this->p25);
		cl -=     21 * cos(this->p19 - this->p25);
		cl +=     20 * sin(this->p25 - this->p28);
		cl +=     20 * cos(this->p22 - 2 * this->p25);
		cl -=     19 * cos(this->p22 - this->p25);
		cl +=     17 * sin(2 * this->p25 - 3 * this->p28);
		cl +=     14 * sin(3 * this->p25 - 3 * this->p28);
		cl +=     13 * sin(this->p22 - this->p25);
		cl -=     12 * this->pt * this->pt * cos(this->p25);
		cl -=     12 * cos(this->p25);
		cl +=     10 * sin(2 * this->p25 - 2 * this->p28);
		cl -=      9 * sin(2 * this->p26);
		cl -=      9 * this->pt * this->pt * sin(this->p25);
		cl +=      9 * cos(2 * this->p25 - 3 * this->p28);
		cl +=      8 * this->pt * cos(this->p22 - 2 * this->p25);
		cl +=      7 * this->pt * cos(this->p22 - 3 * this->p25);
		cl -=      7 * this->pt * sin(this->p22 - 3 * this->p25);
		cl +=      7 * this->pt * sin(2 * this->p25);
		cl +=      6 * sin(2 * this->p19 - 6 * this->p22 + 2 * this->p25);
		cl +=      6 * cos(2 * this->p19 - 6 * this->p22 + 2 * this->p25);
		cl +=      5 * sin(this->p22 - 4 * this->p25);
		cl -=      4 * sin(3 * this->p25 - 4 * this->p28);
		cl +=      4 * cos(3 * this->p25 - 3 * this->p28);
		cl -=      3 * cos(this->p28);
		cl -=      2 * sin(this->p28);
		
		double cb = 2775 * sin(this->p26);
		cb += 131 * sin(this->p25 - this->p26);
		cb += 130 * sin(this->p25 + this->p26);
		
		double rv = 19.21216;
		rv -= 0.90154 * cos(this->p25);
		rv -= 0.02488 * this->pt * sin(this->p25);
		rv -= 0.02121 * cos(2 * this->p25);
		rv -= 0.00585 * cos(this->p22 - 2 * this->p25);
		rv -= 0.00508 * this->pt * cos(this->p25);
		rv -= 0.00451 * cos(this->p19 - this->p25);
		rv += 0.00336 * sin(this->p22 - this->p25);
		rv += 0.00198 * sin(this->p19 - this->p25);
		rv += 0.00118 * cos(this->p22 - 3 * this->p25);
		rv += 0.00107 * sin(this->p22 - 2 * this->p25);
		rv -= 0.00103 * this->pt * sin(2 * this->p25);
		rv -= 0.00081 * cos(3 * this->p25 - 3 * this->p28);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#****************************#
	# neptune position cal sub 1 #
	#****************************# */
	PlanetPosition Neptune_cal1() {
		double cl = 1296000 * this->p27 / M_PI / 2;
		cl +=   3523 * sin(this->p28);
		cl -=     50 * sin(2 * this->p29);
		cl -=     43 * this->pt * cos(this->p28);
		cl +=     29 * sin(this->p19 - this->p28);
		cl +=     19 * sin(2 * this->p28);
		cl -=     18 * cos(this->p19 - this->p28);
		cl +=     13 * cos(this->p22 - this->p28);
		cl +=     13 * sin(this->p22 - this->p28);
		cl -=      9 * sin(2 * this->p25 - 3 * this->p28);
		cl +=      9 * cos(2 * this->p25 - 2 * this->p28);
		cl -=      5 * cos(2 * this->p25 - 3 * this->p28);
		cl -=      4 * this->pt * sin(this->p28);
		cl +=      4 * cos(this->p25 - 2 * this->p28);
		cl +=      4 * this->pt * this->pt * sin(this->p28);
		
		double cb = 6404 * sin(this->p29);
		cb +=  55 * sin(this->p28 + this->p29);
		cb +=  55 * sin(this->p28 - this->p29);
		cb -=  33 * this->pt * sin(this->p29);
		
		double rv = 30.07175;
		rv -= 0.25701 * cos(this->p28);
		rv -= 0.00787 * cos(2 * this->p24 - this->p25 - 2 * this->p27);
		rv += 0.00409 * cos(this->p19 - this->p28);
		rv -= 0.00314 * this->pt * sin(this->p28);
		rv += 0.00250 * sin(this->p19 - this->p28);
		rv -= 0.00194 * sin(this->p22 - this->p28);
		rv += 0.00185 * cos(this->p22 - this->p28);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#**************************#
	# Pluto position cal sub 1 #
	#**************************# */
	PlanetPosition Pluto_cal1() {
		double cl = 1296000 * this->p31 / M_PI / 2;
		cl += 101577 * sin(this->p32);
		cl +=  15517 * sin(2 * this->p32);
		cl -=   3593 * sin(2 * this->p33);
		cl +=   3414 * sin(3 * this->p32);
		cl -=   2201 * sin(this->p32 - 2 * this->p33);
		cl -=   1871 * sin(this->p32 + 2 * this->p33);
		cl +=    839 * sin(4 * this->p32);
		cl -=    757 * sin(2 * this->p32 + 2 * this->p33);
		cl -=    285 * sin(3 * this->p32 + 2 * this->p33);
		cl +=    227 * this->pt * this->pt * sin(this->p32);
		cl +=    218 * sin(2 * this->p32 - 2 * this->p33);
		cl +=    200 * this->pt * sin(this->p32);
		
		double cb = 57726 * sin(this->p33);
		cb +=15257 * sin(this->p32 - this->p33);
		cb +=14102 * sin(this->p32 + this->p33);
		cb += 3870 * sin(2 * this->p32 + this->p33);
		cb += 1138 * sin(3 * this->p32 + this->p33);
		cb +=  472 * sin(2 * this->p32 - this->p33);
		cb +=  353 * sin(4 * this->p32 + this->p33);
		cb -=  144 * sin(this->p32 - 3 * this->p33);
		cb -=  119 * sin(3 * this->p33);
		cb -=  111 * sin(this->p32 + 3 * this->p33);
		
		double rv = 40.74638;
		rv -= 9.58235 * cos(this->p32);
		rv -= 1.16703 * cos(2 * this->p32);
		rv -= 0.22649 * cos(3 * this->p32);
		rv -= 0.04996 * cos(4 * this->p32);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}


/*	#*************************************#
	# pluto position cal sub 2            #
	#*************************************# */
	PlanetPosition Pluto_cal2(double jd) {
		double t = (jd - 2451545.0) / 36525;
		
		double cl = 241.82574;
		cl +=179.09519 * t;
		cl += 15.81087 * this->Cosd( 246.556453 * t + 298.348019);
		cl +=  1.18379 * this->Cosd( 551.34710  * t + 351.67676);
		cl +=  0.07886 * this->Cosd( 941.622    * t +  41.989);
		cl +=  0.00861 * this->Cosd(2836.46     * t +  60.35);
		cl +=  0.00590 * this->Cosd(1306.75     * t + 112.91);
		cl +=  0.00145 * this->Cosd(2488.14     * t +  19.01);
		cl +=  0.00022 * this->Cosd(5861.8      * t +  77.9);
		cl +=  0.00013 * this->Cosd(3288.8      * t + 293.0);
		cl *= 3600;
		
		double cb = 17.04550 * this->Cosd( 172.554318 * t+ 42.574982);
		cb += 2.45310 * this->Cosd( 415.60630  * t+ 66.15350);
		cb -= 2.30285;
		cb += 0.26775 * this->Cosd( 713.1227   * t + 105.0840);
		cb += 0.01855 * this->Cosd(1089.202    * t + 146.660);
		cb += 0.00119 * this->Cosd(2658.22     * t + 293.06);
		cb += 0.00098 * this->Cosd(3055.6      * t + 18.8);
		cb += 0.00090 * this->Cosd(1532.6      * t + 213.7);
		cb += 0.00042 * this->Cosd(2342.3      * t + 254.2);
		cb *= 3600;
		
		double rv = 38.662489;
		rv += 8.670489 * this->Cosd( 181.3383 * t + 198.4973);
		rv += 0.333884 * this->Cosd( 475.963  * t + 228.717);
		rv += 0.008426 * this->Cosd( 909.8    * t + 252.9);
		rv += 0.007619 * this->Cosd(1425.9    * t +  31.0) * t;
		rv += 0.004902 * this->Cosd(2831.6    * t + 149.4);
		rv += 0.002543 * this->Cosd(2196.1    * t + 199.5) * t;
		rv += 0.001188 * this->Cosd(1748.0    * t + 114.1);
		rv += 0.000390 * this->Cosd(3188      * t +  15);
		rv += 0.000116 * this->Cosd(5860      * t + 169);
		
		PlanetPosition ret = {cl, cb, rv};
		return ret;
	}

/*	#*****************************************************#
	# planet geocentric ecliptic position calculate sub   #
	#   input  : jd    = julian day                       #
	#   output : pcl[] = planet celestial longitude [rad] #
	#            pcb[] = planet celestial latitude  [rad] #
	#*****************************************************#	*/
	void Planet_calc(double jd, int maxPlanet) {
		// Aberration_of_light
		double c[ePLANET_MAX] = {
			0.0,	// sun
			0.0,	// moon
			0.0035, //-mercury
			0.0048, //-venus
			0.0071, //-mars
			0.0129, //-jupiter
			0.0174, //-saturn
			0.0249, //-uranus
			0.0312, //-neptune
			0.0347, //-pluto
		};
		
		this->calcPlanetParamaters(jd);		// -calculate planet parameter

		PlanetPosition pp = {0.0, 0.0, 0.0};
		double gcl = 0.0;
		double gcb = 0.0;
		double sl = 0.0;
		double sr = 0.0;
		double sx= 0.0;
		double sy= 0.0;
		for(int i = 0; i < maxPlanet; i++) {
			if (i == 0) {	// -sun position cal
				pp = this->Sun_cal1();
				gcl = pp.longitude / 1296000;
				gcl = (gcl - floor(gcl)) * M_PI * 2;
				gcb = pp.latitude;
				sl = gcl;
				sr = pp.rv;
				sx = pp.rv * cos(gcl);
				sy = pp.rv * sin(gcl);
				gcl -= 0.0057 * M_PI / 180.0;	//-apparent longitude of sun
			}
			else if (i == 1) {	//-moon position cal
				pp  = this->Moon_cal1();
				gcl = pp.longitude * M_PI / 648000.0;
				gcb = pp.latitude * M_PI / 648000.0;
			}

			else {	//-planet position cal
				if (i == 2) {
					pp = this->Mercury_cal1();
				}
				else if (i == 3) {
					pp = this->Venus_cal1();
				}
				else if (i == 4) {
					pp = this->Mars_cal1();
				}
				else if (i == 5) {
					pp = this->Jupiter_cal1();
				}
				else if (i == 6) {
					pp = this->Saturn_cal1();
				}
				else if (i == 7) {
					pp = this->Uranus_cal1();
				}
				else if (i == 8) {
					pp = this->Neptune_cal1();
				}

				else {
					if ((jd > 2432384.28546) && (jd < 2479514.98634)) {
						pp = this->Pluto_cal2(jd);	//-1947 - 2076
					}
					else {
						pp = this->Pluto_cal1();
					}
				}
				
				pp.longitude /= 1296000.0;
				pp.longitude = (pp.longitude - floor(pp.longitude)) * M_PI * 2.0;
				pp.latitude *= M_PI / 648000.0;

				//-change geocentric
				double x = pp.rv * cos(pp.latitude) * cos(pp.longitude) + sx;
				double y = pp.rv * cos(pp.latitude) * sin(pp.longitude) + sy;
				double z = pp.rv * sin(pp.latitude);
				double grv = sqrt(x * x + y * y + z * z);
				gcb = asin(z / grv);
				gcl = atan2(y, x);
				gcl -= (0.0057 * M_PI / 180) / sr * cos(gcl - sl) + (c[i] * M_PI / 180) / pp.rv * cos(gcl - pp.longitude);
			}

			gcl /= M_PI * 2;	//-longitude normalize
			this->m_pcl[i] = (gcl - floor(gcl)) * M_PI * 2;
			this->m_pcb[i] = gcb;
		}
	}

/*	#=========================================================================
	#-各惑星のハウス位置を調べる
	#=========================================================================
	#	○戻り値
	#		house_pos	※[0-11]に第１〜第12ハウスに入る惑星の番号が入る
	#					（2byte * n個の惑星）
	#		pl_pos		※[0-9]（各惑星の番号）に01-12のハウス番号が入る
	#========================================================================= */
	void get_house_pos(int maxPlanet){
		double casp_w[cHOUSE_MAX];
		for(int i = 0; i < cHOUSE_MAX; i++){
			casp_w[i] = this->m_casp_pcl[i];
		}

		typedef struct PlanetSort_t{
			int		planet;
			double	pcl;
		}PlanetSort;

		PlanetSort planet_s1[ePLANET_MAX];
		PlanetSort planet_s2[ePLANET_MAX];
		for (int i = 0; i < ePLANET_MAX; i++) {
			planet_s1[i].planet = i;
			planet_s1[i].pcl = this->m_pcl[i]*60.0;
			planet_s2[i] = planet_s1[i];
		}

		// 惑星の位置をASCに近いものから順番に並べる
		for (int i = 0; i < maxPlanet - 1; i++) {
			for (int j = i; j < maxPlanet - 1; j++) {
				if (planet_s2[j].pcl > planet_s2[j + 1].pcl) {
					PlanetSort tmp = planet_s2[j];
					planet_s2[j] = planet_s2[j + 1];
					planet_s2[j + 1] = tmp;
				}
			}
		}

		int wk_i = 0;
		for (wk_i = 0; wk_i < maxPlanet; wk_i++) {
			if (planet_s2[wk_i].pcl >= casp_w[0] * 60) {
				break;
			}
		}

		if ((wk_i == 0) || (wk_i == maxPlanet)) {
			for(int i = 0; i < maxPlanet; i++){
				planet_s1[i] = planet_s2[i];
			}
		}
		else {
			for(int i = 0; i < maxPlanet; i++){
				planet_s1[i] = planet_s2[(wk_i + i)%ePLANET_MAX];
			}
		}

		for (int i = 0; i < maxPlanet; i++) {
			for (int j = 0; j < cHOUSE_MAX; j++) {
				double pl_angle = planet_s1[i].pcl;
				int pl_num = planet_s1[i].planet;
				double casp1 = casp_w[j] * 60;
				double casp2 = 0.0;

				if (j == (cHOUSE_MAX - 1)) {
					casp2 = casp_w[0] * 60;
				}
				else {
					casp2 = casp_w[j + 1] * 60;
				}

				if (casp2 < casp1) {
					if ((pl_angle >= casp1) || (pl_angle < casp2)) {
						this->m_pl_pos[pl_num] = j;
						break;
					}
				}
				else {
					if ((pl_angle >= casp1) && (pl_angle < casp2)) {
						this->m_pl_pos[pl_num] = j;
						break;
					}
				}
			}
		}
	}
	
/*	#=========================================================================
	#-Main routine
	#=========================================================================
	#	○引数
	#	jd
	#	lon	緯度
	#	lat	経度
	#
	#		--惑星--
	#		        星座        角度1       角度2        順逆
	#		太陽    sign[0]    pcl[0]     pcl2[0]     prm[0]
	#		月      sign[1]    pcl[1]     pcl2[1]     prm[1]
	#		水星    sign[2]    pcl[2]     pcl2[2]     prm[2]
	#		金星    sign[3]    pcl[3]     pcl2[3]     prm[3]
	#		火星    sign[4]    pcl[4]     pcl2[4]     prm[4]
	#		木星    sign[5]    pcl[5]     pcl2[5]     prm[5]
	#		土星    sign[6]    pcl[6]     pcl2[6]     prm[6]
	#		天王星  sign[7]    pcl[7]     pcl2[7]     prm[7]
	#		海王星  sign[8]    pcl[8]     pcl2[8]     prm[8]
	#		冥王星  sign[9]    pcl[9]     pcl2[9]     prm[9]
	#
	#		--カスプ--
	#		        星座        角度1       角度2
	#		第１室  sign[10]   pcl[10]    pcl2[10]
	#		第２室  sign[11]   pcl[11]    pcl2[11]
	#		第３室  sign[12]   pcl[12]    pcl2[12]
	#		第４室  sign[13]   pcl[13]    pcl2[13]
	#		第５室  sign[14]   pcl[14]    pcl2[14]
	#		第６室  sign[15]   pcl[15]    pcl2[15]
	#		第７室  sign[16]   pcl[16]    pcl2[16]
	#		第８室  sign[17]   pcl[17]    pcl2[17]
	#		第９室  sign[18]   pcl[18]    pcl2[18]
	#		第10室  sign[19]   pcl[19]    pcl2[19]
	#		第11室  sign[20]   pcl[20]    pcl2[20]
	#		第12室  sign[21]   pcl[21]    pcl2[21]
	#========================================================================= */
	void getSpherePos(double jd, double lon, double lat, int maxPlanet) {
		
		double t = (jd - 2451545) / 36525;
		
		double e = 23.43928 - 0.01301 * t;
		e += 0.00256 * this->Cosd( 1934 * t + 235);
		e += 0.00016 * this->Cosd(72002 * t + 201);
		e *= M_PI / 180;	// e value [rad]
	
		t = jd - 2442412.5;	// from 1975 jan/0 0:0
		double tt = t - floor(t);
		t /= 365.25;
		
		double st = 99.0361 + 360.00770 * t + 360 * tt;	// greenwich sideral time get
		st += 0.0044 * this->Sind(-19.3 * t + 68.6);
		st += 0.0003 * this->Sind(720 * t + 18);

		st = st * M_PI / 180 + lon;	// local sideral time get
		st /= M_PI * 2;	// value normalize
		st -= floor(st);
		st *= M_PI * 2;	// local sideral time value [rad]
		
		// ascendant cal-#
		double x = cos(st + M_PI / 2) * cos(e) + sin(e) / tan(lat + M_PI / 2);
		double y = sin(st + M_PI / 2);
		double asc = atan2(y, x);	// ascendant celestial position [rad]
		if (asc < 0) {
			asc += M_PI * 2.0;
		}

		// house casp cal
		this->m_casp_pcl[0] = asc;			// ascendant set
		this->m_casp_pcl[6] = asc + M_PI;	// descendant set
		
		for (int i = 1; i < cHOUSE_MAX/2; i++) {
			double ccl1 = this->m_casp_pcl[i - 1];	// min angle set
			double ccl2 = asc + M_PI;				// max angle
			double ccle = i * M_PI / 6.0;				// target angle
			double cl = 0.0;
			
			while (1) {
				cl = (ccl1 + ccl2) / 2.0;
				
				// translate ecliptic to equatorial
				double x = cos(cl);
				double y = sin(cl) * cos(e);
				double z = sin(cl) * sin(e);
				double ra = atan2(y, x);
				if (ra < 0) {
					ra += M_PI * 2;
				}
				double dc = asin(z);
				
				// translate equatorial to placidus house angle
				double ct = -tan(lat) * tan(dc);
				if ((ct < -1.0) || (ct > 1.0)) {
					cl = 0.0;		// -cal impossible
					break;
				}
				tt = acos(ct);		// -rise & set cal
				t = st - ra;		// -hour angle cal

				if (t < -M_PI) {
					t += M_PI * 2.0;
				}
				else if (t > M_PI) {
					t -= M_PI * 2.0;
				}

				double ha = 0.0;
				if ((t >= -(tt)) && (t <= tt)) {	// above the horison
					ha = M_PI/2.0 * (3 - t / tt);
				}
				else {	// below the horison
					t += M_PI;
					if (t > M_PI) {
						t -= M_PI * 2.0;
					}
					ha = (1 - t / (M_PI - tt)) * M_PI / 2.0;
				}
				if (ha < 0.0) {
					ha += M_PI * 2.0;
				}
				else if (ha >= M_PI * 2.0) {
					ha -= M_PI * 2.0;
				}
				
				ha -= ccle;
				if (ha > 0.0) {
					ccl2 = cl;
				}
				else {
					ccl1 = cl;
				}
				if (fabs(ha) < 0.000001) {
					break;
				}
			}
			this->m_casp_pcl[i] = cl;
			this->m_casp_pcl[i + 6] = cl + M_PI;
		}
		
		for(int i = 0; i < cHOUSE_MAX; i++) {
			if (this->m_casp_pcl[i] >= M_PI * 2) {
				this->m_casp_pcl[i] -= M_PI * 2;
			}
			this->m_casp_pcl[i] = this->m_casp_pcl[i] * 180 / M_PI;
		}
		
		// planets dairy motion cal-
		this->Planet_calc(jd + 0.5, maxPlanet);
		for (int i = 0; i < ePLANET_MAX; i++) {
			this->m_pdm[i] = this->m_pcl[i];
		}

		this->Planet_calc(jd - 0.5, maxPlanet);
		for (int i = 0; i < ePLANET_MAX; i++) {
			this->m_pdm[i] -= this->m_pcl[i];
			if (this->m_pdm[i] > M_PI) {
				this->m_pdm[i] -= M_PI * 2;
			}
			else if (this->m_pdm[i] < -(M_PI)) {
				this->m_pdm[i] += M_PI * 2;
			}
		}
		
		// planets position cal
		this->Planet_calc(jd, maxPlanet);
		for (int i = 0; i < ePLANET_MAX; i++) {
			double cl = this->m_pcl[i];
			double cb = this->m_pcb[i];
			
			// translate ecliptic to equatorial
			x = cos(cl) * cos(cb);
			y = sin(cl) * cos(cb) * cos(e) - sin(cb) * sin(e);
			double z  = sin(cb) * cos(e) + cos(cb) * sin(cl) * sin(e);
			double ra = atan2(y, x);
			if(ra < 0){
				ra += 2.0 * M_PI;
			}
			double dc = asin(z);
			
			this->m_pra[i] = (ra * 180 / M_PI);
			this->m_pcl[i] = (cl * 180 / M_PI);
			this->m_pdc[i] = (dc * 180 / M_PI);
			// 2014.10.24 add by kyon 緯度のラジアンを角度に戻した
			this->m_pcb[i] = (cb * 180 / M_PI);
		}
		
		for (int i = 0; i < ePLANET_MAX; i++) {
			double mm = this->m_pcl[i] * 60.0;
			double si = floor(mm / 1800.0);
			mm -= si * 1800.0;
			double dd = floor(mm / 60.0);
			mm -= dd * 60.0;
			this->m_sign[i] = (int)si;
			if (this->m_pdm[i] < 0) {
				this->m_prm[i] = 'R';
			}
			else {
				this->m_prm[i] = 'P';
			}
			char buff[256];
			sprintf(buff, "%02d%02d", (int)dd, (int)mm);
			this->m_pcl2[i] = atoi(buff);
		}

		for (int i = 0; i < cHOUSE_MAX; i++) {
			double mm = this->m_casp_pcl[i] * 60.0;
			double si = floor(mm / 1800.0);
			mm -= si * 1800.0;
			double dd = floor(mm / 60.0);
			mm -= dd * 60.0;
			this->m_casp_sign[i] = (int)si;

			char buff[256];
			sprintf(buff, "%02d%02d", (int)dd, (int)mm);
			this->m_casp_pcl2[i] = atoi(buff);
		}

		this->get_house_pos(maxPlanet);
	}
};

#endif

