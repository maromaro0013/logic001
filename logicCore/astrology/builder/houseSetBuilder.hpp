// 2014-11-19 y_ohta

#ifndef _ASTROLOGYHOUSESETBUILDER_HPP_
#define _ASTROLOGYHOUSESETBUILDER_HPP_

#include "../../../core/julianDate.hpp"
#include "../../astronomy/houseSet.hpp"
#include "../../astronomy/planetSet.hpp"

#include "../../astronomy/lowPrecPlanetaryEphemeris.hpp"

class houseSetBuilder {
private:
	double				m_siderealTime;
	double				m_obliquity;
	double				m_latitude;

	double				m_radSidTime;
	double				m_radObliquity;
	double				m_radLatitude;

public:
	houseSetBuilder() {
	}
	~houseSetBuilder() {
	}

	void setSiderealTime(double sidTime) {
		m_siderealTime = sidTime;
		m_radSidTime = deg2rad(sidTime);
	}
	void setObliquity(double obl) {
		m_obliquity = obl;
		m_radObliquity = deg2rad(obl);
	}
	void setLatitude(double lat) {
		m_latitude = lat;
		m_radLatitude = deg2rad(lat);
	}

	astrologyHouseSet* generate() {
		double asc = this->calculateAscendant();
		double mc = this->calculateMediumCoeli();

		double cusp_ary[cHOUSE_MAX];

		for(int i = 0; i < cHOUSE_MAX; i++) {
			switch (i) {
				case 0:
					cusp_ary[i] = asc;
					break;
				case 3:
					cusp_ary[i] = fmod(mc + 180.0, 360.0);
					break;
				case 6:
					cusp_ary[i] = fmod(asc + 180.0, 360.0);
					break;
				case 9:
					cusp_ary[i] = mc;
					break;

				default:
					double d0 = 1.0e-03;
					double d = 0.0;
					int nh = i + 1;

					if(3 <= i && i < 9){
						nh = (nh + 6)%cHOUSE_MAX;
						if(nh == 0){
							nh = cHOUSE_MAX;
						}
					}

					double H = deg2rad(fmod((nh + 2) * 30.0, 360.0));
					double F = (nh % 2 == 1 ) ? 3.0 : 1.5;

					double X0 = m_radSidTime + H;
					double X1 = 0.0;
					double P0 = 0.0;
					double P1 = 0.0;
					do {
						P0  = sin(X0) * tan(m_radObliquity ) * tan(m_radLatitude);
						P0 *= (nh > 7) ? -1.0 : +1.0;
						P1  = ( (nh > 7) ? +1.0 : -1.0 ) * acos(P0);
						X1  = m_radSidTime + P1 / F + ((nh > 7) ? 0.0 : M_PI);
						d = fabs(X0 - X1);
						X0 = X1;
					} while(d > d0);
					double csp_x = sin(X1);
					double csp_y = cos(m_radObliquity) * cos(X1);
					double csp = rad2deg(atan2(csp_x, csp_y ));
					csp += (3 <= i && i < 9) ? 180.0 : 0.0;
					if(csp < 0.0 ){
						csp += 360.0;
					}
					else if(csp >= 360.0){
						csp -= 360.0;
					}
					cusp_ary[i] = csp;

					break;
			}
		}

		astrologyHouseSet* ret = new astrologyHouseSet();
		for (int i = 0; i < cHOUSE_MAX; i++) {
			astrologyHouse *house = ret->getHouse(i);
			house->setCuspLongitude(cusp_ary[i]);
		}

		return ret;
	}

private:
	double calculateAscendant() {
		double asc_x = cos(m_radSidTime);
		double asc_y = -(sin(m_radObliquity) * tan(m_radLatitude));
		asc_y -= cos(m_radObliquity) * sin(m_radSidTime);
		
		double asc = rad2deg(atan2(asc_x, asc_y));
		if(asc < 0.0){
			asc += 360.0;
		}
		return asc;
	}
	
	double calculateMediumCoeli(){
		double mc_x = sin(m_radSidTime);
		double mc_y = cos(m_radSidTime) * cos(m_radObliquity);
		double mc = rad2deg(atan2(mc_x, mc_y));
		if(mc < 0.0){
			mc += 360.0;
		}
		return mc;
	}
};

#endif

