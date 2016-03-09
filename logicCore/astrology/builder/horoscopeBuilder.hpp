// 2015-01-06 y_ohta

#ifndef _HOROSCOPEBUILDER_HPP_
#define _HOROSCOPEBUILDER_HPP_

#include "../../../core/julianDate.hpp"
#include "../../astronomy/astronomicalCalculation.hpp"
#include "../../astronomy/houseSet.hpp"
#include "../../astronomy/planetSet.hpp"

#include "../../astronomy/lowPrecPlanetaryEphemeris.hpp"

class horoscopeBuilder {
private:
	double				m_longitude;
	double				m_latitude;

	int					m_maxPlanet;
	JulianDate*			m_date;
	houseSetBuilder*	m_hSetBuilder;
	
public:
	horoscopeBuilder() {
		m_longitude = 0.0f;
		m_latitude = 0.0f;

		m_maxPlanet = ePLANET_MAX;
		m_date = new JulianDate();
		m_hSetBuilder = new houseSetBuilder();
	}
	~horoscopeBuilder() {
		if (m_date != NULL) {
			delete m_date;
		}
		if (m_hSetBuilder != NULL) {
			delete m_hSetBuilder;
		}
	}

	void setDate(int year, int month, int day) {
		m_date->setDate(year, month, day);
	}
	void setTime(int hour, int min, int sec) {
		m_date->setTime(hour, min, sec);
	}
	void setDateTime(const Date* date) {
		m_date->setDate(date->getYear(), date->getMonth(), date->getDay());
		m_date->setTime(date->getHour(), date->getMin(), date->getSec());
	}
	void addDays(int days) {
		m_date->addDays(days);
	}
	void subDays(int days) {
		m_date->subDays(days);
	}
	const JulianDate* getDate(void) {
		return m_date;
	}

	void setLongitude(double l) {
		m_longitude = l;
	}
	void setLatitude(double l) {
		m_latitude = l;
	}

	void setMaxPlanet(int planet) {
		if (m_maxPlanet <= ePLANET_MAX) {
			m_maxPlanet = planet;
		}
	}

	astrologyHoroscope* generate() {
		astrologyHoroscope* ret = new astrologyHoroscope();
		this->generate(ret);
		return ret;
	}

	void generate(astrologyHoroscope* dest) {
		dest->deleteParams();

		double julianDay = m_date->calculateJulianDayJST();
		dest->setJulianDay(julianDay);

		astrologyPlanetSet* planetSet = new astrologyPlanetSet();
		dest->setPlanetSet(planetSet);

		double jd = m_date->calculateJulianDayJST();
		planetSet->setPlanetSet(jd, m_longitude, m_latitude, m_maxPlanet);

		double sidTime = astronomyAstronomicalCalculation::calcApparentLocalSiderealTime(*m_date, m_longitude);
		double julianDayTDT = jd + m_date->calculateDeltaT(jd);
		double obl = astronomyAstronomicalCalculation::calcObliquity(julianDayTDT);

		m_hSetBuilder->setSiderealTime(sidTime);
		m_hSetBuilder->setObliquity(obl);
		m_hSetBuilder->setLatitude(m_latitude);

		astrologyHouseSet* houseset = m_hSetBuilder->generate();
		dest->setHouseSet(houseset);

		for (int i = 0; i < ePLANET_MAX; i++) {
			astrologyPlanet* planet = planetSet->getPlanet(i);
			astrologyHouse* planetHouse = planet->getHouse();

			double planetHouseCusp = houseset->getHouse(planetHouse->getHouse())->getCuspLongitude();
			planetHouse->setCuspLongitude(planetHouseCusp);
		}
	}
};

#endif
