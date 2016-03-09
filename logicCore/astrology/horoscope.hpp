// 2014-12-28 y_ohta

#ifndef _HOROSCOPE_HPP_
#define _HOROSCOPE_HPP_

#include "../astronomy/houseSet.hpp"
#include "../astronomy/planetSet.hpp"

class astrologyHoroscope {
private:
	double					m_julianDay;
	double					m_longitude;
	double					m_latitude;

	astrologyHouseSet*		m_houseSet;
	astrologyPlanetSet*		m_planetSet;
	
public:
	astrologyHoroscope() {
		m_julianDay = 0.0f;
		m_longitude = 0.0;
		m_latitude = 0.0;

		m_houseSet = NULL;
		m_planetSet = NULL;
	}
	~astrologyHoroscope() {
		this->deleteParams();
	}

	void setJulianDay(double d) {
		m_julianDay = d;
	}
	double getJulianDay(void) {
		return m_julianDay;
	}

	void setCoordinate (double longitude, double latitude) {
		m_longitude = longitude;
		m_latitude = latitude;
	}

	double getLongitude(void) {
		return m_longitude;
	}
	double getLatitude(void) {
		return m_latitude;
	}

	void setHouseSet(astrologyHouseSet* houseset) {
		m_houseSet = houseset;
	}
	astrologyHouseSet* getHouseSet(void) {
		return m_houseSet;
	}

	void setPlanetSet(astrologyPlanetSet* planetset) {
		m_planetSet = planetset;
	}
	astrologyPlanetSet* getPlanetSet(void) {
		return m_planetSet;
	}

	int getAscendant(void) {
		return astrologySign::getSignFromLongitude(m_houseSet->getHouse(0)->getCuspLongitude());
	}
	int getMC(void) {
		return astrologySign::getSignFromLongitude(m_houseSet->getHouse(9)->getCuspLongitude());
	}

	void printPlanetLongitude(char* buff, int length) {
		sprintf(buff, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		m_planetSet->getPlanet(ePLANET_SUN)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_MOON)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_MERCURY)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_VENUS)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_MARS)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_JUPITER)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_SATURN)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_URANUS)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_NEPTUNE)->getLongitude(),
		m_planetSet->getPlanet(ePLANET_PLUTO)->getLongitude());
	}

	void printPlanetSign(char* buff, int length) {
		sprintf(buff, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_SUN)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_MOON)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_MERCURY)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_VENUS)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_MARS)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_JUPITER)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_SATURN)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_URANUS)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_NEPTUNE)->getSign()->getSign()),
		astrologySign::getJpSignName(m_planetSet->getPlanet(ePLANET_PLUTO)->getSign()->getSign()));
	}

	void printPlanetHouse(char* buff, int length) {
		sprintf(buff, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		m_planetSet->getPlanet(ePLANET_SUN)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_MOON)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_MERCURY)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_VENUS)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_MARS)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_JUPITER)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_SATURN)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_URANUS)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_NEPTUNE)->getHouse()->getHouse() + 1,
		m_planetSet->getPlanet(ePLANET_PLUTO)->getHouse()->getHouse() + 1);
	}

	void printHouseCusp(char* buff, int length) {
		m_houseSet->getHouse(0)->getCuspLongitude();
		sprintf(buff, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
				m_houseSet->getHouse(0)->getCuspLongitude(),
				m_houseSet->getHouse(1)->getCuspLongitude(),
				m_houseSet->getHouse(2)->getCuspLongitude(),
				m_houseSet->getHouse(3)->getCuspLongitude(),
				m_houseSet->getHouse(4)->getCuspLongitude(),
				m_houseSet->getHouse(5)->getCuspLongitude(),
				m_houseSet->getHouse(6)->getCuspLongitude(),
				m_houseSet->getHouse(7)->getCuspLongitude(),
				m_houseSet->getHouse(8)->getCuspLongitude(),
				m_houseSet->getHouse(9)->getCuspLongitude(),
				m_houseSet->getHouse(10)->getCuspLongitude(),
				m_houseSet->getHouse(11)->getCuspLongitude());
	}

	void deleteParams() {
		if (m_houseSet != NULL) {
			delete m_houseSet;
		}
		m_houseSet = NULL;
		if (m_planetSet != NULL) {
			delete m_planetSet;
		}
		m_planetSet = NULL;
	}
};

#endif
