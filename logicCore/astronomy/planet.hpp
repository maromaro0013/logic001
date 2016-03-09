// 2014-12-29 y_ohta

#ifndef _PLANET_HPP_
#define _PLANET_HPP_

#include "sign.hpp"
#include "house.hpp"

// planet
enum {
	ePLANET_SUN = 0,
	ePLANET_MOON = 1,
	ePLANET_MERCURY = 2,
	ePLANET_VENUS = 3,
	ePLANET_MARS = 4,
	ePLANET_JUPITER = 5,
	ePLANET_SATURN = 6,
	ePLANET_URANUS = 7,
	ePLANET_NEPTUNE = 8,
	ePLANET_PLUTO = 9,
	ePLANET_MAX = ePLANET_PLUTO + 1
};

class astrologyPlanet {
private:
	double			m_longitude;
	double			m_latitude;
	double			m_rightAscension;
	double			m_declination;
	double			m_longitudalVelocity;

	astrologySign*	m_sign;
	astrologyHouse*	m_house;
	
public:
	astrologyPlanet() {
		m_longitude = 0.0;
		m_latitude = 0.0;
		m_rightAscension = 0.0;
		m_declination = 0.0;
		m_longitudalVelocity = 0.0;

		m_sign = new astrologySign();
		m_house = new astrologyHouse();
	}
	~astrologyPlanet() {
		if (m_sign != NULL) {
			delete m_sign;
		}
		if (m_house != NULL) {
			delete m_house;
		}
	}

	void setLongitude(double longitude) {
		m_longitude = longitude;
	}
	double getLongitude(void) {
		return m_longitude;
	}

	void setLatitude(double latitude) {
		m_latitude = latitude;
	}
	double getLatitude(void) {
		return m_latitude;
	}

	void setRightAscension(double rightAscension) {
		m_rightAscension = rightAscension;
	}
	double getRightAscension(void) {
		return m_rightAscension;
	}

	void setDeclination(double declination) {
		m_declination = declination;
	}
	double getDeclination(void) {
		return m_declination;
	}

	void setVelocity(double velocity) {
		m_longitudalVelocity = velocity;
	}
	double getVelocity(void) {
		return m_longitudalVelocity;
	}

	void setSign(int sign) {
		m_sign->setSign(sign);
	}
	astrologySign* getSign() {
		return m_sign;
	}

	void setHouse(int house, double lgn) {
		m_house->setHouse(house);
		m_house->setCuspLongitude(lgn);
	}
	astrologyHouse* getHouse() {
		return m_house;
	}

	static const char* getEnglishPlanetName(int planet) {
		static const char names[ePLANET_MAX][16] = {
			"SUN",
			"MOON",
			"MERCURY",
			"VENUS",
			"MARS",
			"JUPITER",
			"SATURN",
			"URANUS",
			"NEPTUNE",
			"PLUTO"
		};
		if (planet < ePLANET_MAX) {
			return names[planet];
		}
		return names[0];
	}

	static const char* getJapanesePlanetName(int planet) {
		static const char names[ePLANET_MAX][16] = {
			"太陽",
			"月",
			"水星",
			"金星",
			"火星",
			"木星",
			"土星",
			"天王星",
			"海王星",
			"冥王星"
		};
		if (planet < ePLANET_MAX) {
			return names[planet];
		}
		return names[0];
	}

	static int getRulerFromSign(int sign, bool isOld) {
		static const int planets[eASTROLOGICALSIGN_MAX] = {
			ePLANET_MARS,
			ePLANET_VENUS,
			ePLANET_MERCURY,
			ePLANET_MOON,
			ePLANET_SUN,
			ePLANET_MERCURY,
			ePLANET_VENUS,
			ePLANET_PLUTO,
			ePLANET_JUPITER,
			ePLANET_SATURN,
			ePLANET_URANUS,
			ePLANET_NEPTUNE
		};

		static const int oldPlanets[eASTROLOGICALSIGN_MAX] = {
			ePLANET_MARS,
			ePLANET_VENUS,
			ePLANET_MERCURY,
			ePLANET_MOON,
			ePLANET_SUN,
			ePLANET_MERCURY,
			ePLANET_VENUS,
			ePLANET_MARS,
			ePLANET_JUPITER,
			ePLANET_SATURN,
			ePLANET_SATURN,
			ePLANET_JUPITER
		};

		if (sign < eASTROLOGICALSIGN_MAX) {
			if (isOld == false) {
				return planets[sign];
			}
			else {
				return oldPlanets[sign];
			}
		}
		return planets[0];
	}
};

#endif
