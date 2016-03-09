// 2015-01-03 y_ohta

#ifndef _DAILYSIGN001_HPP_
#define _DAILYSIGN001_HPP_

#include "../actionBase.hpp"

#include "../../core/japanCoordinate.hpp"

#include "../../logicCore/astrology/aspect.hpp"
#include "../../logicCore/astrology/horoscope.hpp"
#include "../../logicCore/astrology/astrologyUtil.hpp"

#include "../../logicCore/astrology/builder/houseSetBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeImageBuilder.hpp"

class dailySign001 : public actionBase {
private:
	astrologyHoroscope*					m_natal;
	astrologyHoroscope*					m_transit;

	int									m_planetId1;
	int									m_planetId2;
	int									m_planetId3;
	int									m_planetId4;

	int									m_maxNatalPlanet;
	int									m_maxTransitPlanet;

public:
	dailySign001() {
		m_natal = NULL;
		m_transit = NULL;

		m_maxNatalPlanet = ePLANET_MAX;
		m_maxTransitPlanet = ePLANET_MAX;
	}
	~dailySign001() {
		if (m_natal != NULL) {
			delete m_natal;
		}
		if (m_transit != NULL) {
			delete m_transit;
		}
	}

	bool ParseRequest(requestFormatter* request) {
		if (request->getIntParam("bymd1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("bhms1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("ymd") == cREQUEST_PARAM_ERROR) {
			return false;
		}

		m_planetId1 = request->getIntParam("planetId1");
		m_planetId2 = request->getIntParam("planetId2");
		m_planetId3 = request->getIntParam("planetId3");
		m_planetId4 = request->getIntParam("planetId4");

		if (m_planetId1 == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (m_planetId2 == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (m_planetId3 == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (m_planetId4 == cREQUEST_PARAM_ERROR) {
			return false;
		}

		// calc planets
/*
		m_maxNatalPlanet = m_planetId1;
		if (m_planetId1 < m_planetId2) {
			m_maxNatalPlanet = m_planetId2;
		}
		m_maxTransitPlanet = m_planetId3;
		if (m_planetId3 < m_planetId4) {
			m_maxTransitPlanet = m_planetId4;
		}
*/
		int bpref1 = request->getIntParam("bpref1");
		if (bpref1 == cREQUEST_PARAM_ERROR) {
			return false;
		}
		double latitude = japanCoodinate::getLatitudeFromId(bpref1);
		double longitude = japanCoodinate::getLongitudeFromId(bpref1);

		// build natal horoscope
		horoscopeBuilder* hBuilder = new horoscopeBuilder();
		hBuilder->setDateTime(request->getBymd1());
		hBuilder->setLatitude(latitude);
		hBuilder->setLongitude(longitude);
		m_natal = hBuilder->generate();

		// build transit horoscope
		int pref = request->getIntParam("pref");
		if (pref == cREQUEST_PARAM_ERROR) {
			return false;
		}
		latitude = japanCoodinate::getLatitudeFromId(pref);
		longitude = japanCoodinate::getLongitudeFromId(pref);
		hBuilder->setDateTime(request->getYmd());
		hBuilder->setTime(12, 0, 0);
		hBuilder->setLatitude(latitude);
		hBuilder->setLongitude(longitude);
		m_transit = hBuilder->generate();

		delete hBuilder;

		return true;
	}

	bool Run(requestFormatter* request) {
		char data[0xffff];

		formatterBase* myProf = m_top->addChild("myProf", NULL, 0);

		// natal horoscope
		{
			formatterBase* datePref = myProf->addChild("datePref", NULL, 0);
			request->getStringParam("bymd1", data);
			datePref->addChild("ymd", data, (int)strlen(data) + 1);
			request->getStringParam("bhms1", data);
			datePref->addChild("hms", data, (int)strlen(data) + 1);
			request->getStringParam("bpref1", data);
			datePref->addChild("pref", data, (int)strlen(data) + 1);
			
			formatterBase* horoscope = myProf->addChild("horoscope", NULL, 0);
			
			// ------------------
			formatterBase* planetState = horoscope->addChild("planetState", NULL, 0);
			m_natal->printPlanetLongitude(data, sizeof(data));
			planetState->addChild("planet", data, (int)strlen(data) + 1);
			
			m_natal->printPlanetSign(data, sizeof(data));
			planetState->addChild("sign", data, (int)strlen(data) + 1);
			
			m_natal->printPlanetHouse(data, sizeof(data));
			planetState->addChild("house", data, (int)strlen(data) + 1);
			// ------------------
			
			// ------------------
			formatterBase* houseState = horoscope->addChild("houseState", NULL, 0);
			int asc = m_natal->getAscendant();
			sprintf(data, "%s", astrologySign::getJpSignName(asc));
			houseState->addChild("asc", data, (int)strlen(data) + 1);
			
			int mc = m_natal->getMC();
			sprintf(data, "%s", astrologySign::getJpSignName(mc));
			houseState->addChild("mc", data, (int)strlen(data) + 1);
			
			m_natal->printHouseCusp(data, sizeof(data));
			houseState->addChild("houseCusp", data, (int)strlen(data) + 1);
			// ------------------
			
			if (m_simpleSwitch == false) {
				// horoscopeImage
				formatterBase* horoscopeImage = horoscope->addChild("horoscopeImage", NULL, 0);
				horoscopeImageBuilder* image = new horoscopeImageBuilder();
				image->convertCoordinate(m_natal);
				image->PrintBase(data, sizeof(data));
				horoscopeImage->addChild("base", data, (int)strlen(data) + 1);
			
				image->PrintPlanetX(data, sizeof(data));
				horoscopeImage->addChild("planetX", data, (int)strlen(data) + 1);
				image->PrintPlanetY(data, sizeof(data));
				horoscopeImage->addChild("planetY", data, (int)strlen(data) + 1);
			}
		}

		formatterBase* transit = m_top->addChild("transit", NULL, 0);

		// transit horoscope
		{
			formatterBase* datePref = transit->addChild("datePref", NULL, 0);
			request->getStringParam("ymd", data);
			datePref->addChild("ymd", data, (int)strlen(data) + 1);
			strcpy(data, "120000");
			datePref->addChild("hms", data, (int)strlen(data) + 1);
			request->getStringParam("pref", data);
			datePref->addChild("pref", data, (int)strlen(data) + 1);
			
			formatterBase* horoscope = transit->addChild("horoscope", NULL, 0);
			
			// ------------------
			formatterBase* planetState = horoscope->addChild("planetState", NULL, 0);
			m_transit->printPlanetLongitude(data, sizeof(data));
			planetState->addChild("planet", data, (int)strlen(data) + 1);
			
			m_transit->printPlanetSign(data, sizeof(data));
			planetState->addChild("sign", data, (int)strlen(data) + 1);
			
			m_transit->printPlanetHouse(data, sizeof(data));
			planetState->addChild("house", data, (int)strlen(data) + 1);
			// ------------------
			
			// ------------------
			formatterBase* houseState = horoscope->addChild("houseState", NULL, 0);
			int asc = m_transit->getAscendant();
			sprintf(data, "%s", astrologySign::getJpSignName(asc));
			houseState->addChild("asc", data, (int)strlen(data) + 1);
			
			int mc = m_transit->getMC();
			sprintf(data, "%s", astrologySign::getJpSignName(mc));
			houseState->addChild("mc", data, (int)strlen(data) + 1);
			
			m_transit->printHouseCusp(data, sizeof(data));
			houseState->addChild("houseCusp", data, (int)strlen(data) + 1);
			// ------------------

			if (m_simpleSwitch == false) {
				// horoscopeImage
				formatterBase* horoscopeImage = horoscope->addChild("horoscopeImage", NULL, 0);
				horoscopeImageBuilder* image = new horoscopeImageBuilder();
				image->convertCoordinate(m_transit);
				image->PrintBase(data, sizeof(data));
				horoscopeImage->addChild("base", data, (int)strlen(data) + 1);
				
				image->PrintPlanetX(data, sizeof(data));
				horoscopeImage->addChild("planetX", data, (int)strlen(data) + 1);
				image->PrintPlanetY(data, sizeof(data));
				horoscopeImage->addChild("planetY", data, (int)strlen(data) + 1);
			}
		}

		// tag
		{
			astrologyPlanetSet* natalPlanetSet = m_natal->getPlanetSet();
			double Longitude1 = natalPlanetSet->getPlanet(m_planetId1)->getLongitude();
			double Longitude2 = natalPlanetSet->getPlanet(m_planetId2)->getLongitude();
			double natalMidPoint = astrologyUtil::calcMidPoint(Longitude1, Longitude2);

			astrologyPlanetSet* transitPlanetSet = m_transit->getPlanetSet();
			double Longitude3 = transitPlanetSet->getPlanet(m_planetId3)->getLongitude();
			double Longitude4 = transitPlanetSet->getPlanet(m_planetId4)->getLongitude();
			double transitMidPoint = astrologyUtil::calcMidPoint(Longitude3, Longitude4);

			double degree = astrologyUtil::degree_normalize(natalMidPoint + transitMidPoint);

			// * 360度を5度区切りで区切って、180度で折り返すと考えた時、何番目に入るかを求める。
			// *
			// * 0～4度は1番目、5～9度は2番目... 175～179度は35番目
			// * 180～184度は1番目、185～189度は2番目...
			int id = (int)((degree / 5.0) + 1) % 36;
			if (id == 0) {
				id++;
			}

			double jd = m_transit->getJulianDay();
			// 25日毎に 1, 2, 3, 4, 1, 2, 3.....とパターンが切り替わっていく。
			int pattern = (int)(jd / 25.0) % 4 + 1;

			// 原稿コードを取得する。 1 ～ 36 と 1 ～ 4 の組み合わせで 144 パターン
			char tag[0xff];
			char pattern_str[0xff];
			sprintf(tag, "%02d", id);
			sprintf(pattern_str, "%d", pattern);
			strcat(tag, pattern_str);

			m_top->addChild("tag", tag, (int)strlen(tag) + 1);
		}
		return true;
	}
};

#endif
