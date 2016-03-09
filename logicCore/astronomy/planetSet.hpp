// 2014-11-13 y_ohta

#ifndef _PLANETSET_HPP_
#define _PLANETSET_HPP_

#define deg2rad(a) ( (a) / 180.0 * M_PI )
#define rad2deg(a) ( (a) / M_PI * 180.0 )

#include "planet.hpp"
#include "lowPrecPlanetaryEphemeris.hpp"

class astrologyPlanetSet {
private:
	astrologyPlanet*		m_planetArr[ePLANET_MAX];
	
public:
	astrologyPlanetSet() {
		for (int i = 0; i < ePLANET_MAX; i++) {
			m_planetArr[i] = new astrologyPlanet();
		}
	}
	~astrologyPlanetSet() {
		for (int i = 0; i < ePLANET_MAX; i++) {
			delete m_planetArr[i];
		}
	}

	astrologyPlanet* getPlanet(int planet) {
		if (planet < ePLANET_MAX) {
			return m_planetArr[planet];
		}
		return m_planetArr[0];
	}

	void setPlanetSet(double jd, double lon, double lat, int maxPlanet) {
		lowPrecPlanetaryEphemeris* ephem = new lowPrecPlanetaryEphemeris();
		ephem->getSpherePos(jd, deg2rad(lon), deg2rad(lat), maxPlanet);

		for (int i = 0; i < ePLANET_MAX; i++) {
			double pcl = ephem->getPlanetaryLongitude(i);
			double pcb = ephem->getPlanetaryLatitude(i);
			double pra = ephem->getPlanetaryRightAscension(i);
			double pdc = ephem->getPlanetaryDeclination(i);
			double pdm = ephem->getPlanetaryVelocity(i);
			int sgn = ephem->getPlanetarySign(i);
			int hse = (int)ephem->getPlanetaryHouse(i);

			m_planetArr[i]->setLongitude(pcl);
			m_planetArr[i]->setLatitude(pcb);
			m_planetArr[i]->setRightAscension(pra);
			m_planetArr[i]->setDeclination(pdc);
			m_planetArr[i]->setVelocity(rad2deg(pdm));
			m_planetArr[i]->setSign(sgn);
			m_planetArr[i]->setHouse(hse, 0.0);
		}

		delete ephem;
	}
};

#endif
