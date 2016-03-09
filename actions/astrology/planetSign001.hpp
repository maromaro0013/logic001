// 2014-12-29 y_ohta

/*-----------------------------------------------------------------------------
 *  planet sign
 *	指定された天体のサインを求める
 *
 *	必要なパラメータ
 *	bymd1:生年月日(yyyymmdd形式)
 *	bhms1:生時分秒(hhmmss形式)
 *	bpref1:出生地(都道府県コード)
 *	planetId:見たい天体(0-9)
 *----------------------------------------------------------------------------*/

#ifndef _PLANETSIGN001_HPP_
#define _PLANETSIGN001_HPP_

#include "../actionBase.hpp"

#include "../../core/japanCoordinate.hpp"

#include "../../logicCore/astrology/aspect.hpp"
#include "../../logicCore/astrology/horoscope.hpp"
#include "../../logicCore/astrology/astrologyUtil.hpp"

#include "../../logicCore/astrology/builder/houseSetBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeImageBuilder.hpp"

class planetSign001 : public actionBase {
private:
	astrologyHoroscope*					m_natal;
	int									m_planetId;

public:
	planetSign001() {
		m_natal = NULL;
	}
	~planetSign001() {
		if (m_natal != NULL) {
			delete m_natal;
		}
	}

	bool ParseRequest(requestFormatter* request) {
		if (request->getIntParam("bymd1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("bhms1") == cREQUEST_PARAM_ERROR) {
			return false;
		}

		m_planetId = request->getIntParam("planetId");


		if (m_planetId == cREQUEST_PARAM_ERROR) {
			return false;
		}

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
		}

		// tag
		{
			int sign = m_natal->getPlanetSet()->getPlanet(m_planetId)->getSign()->getSign();
			char tag[0xff];
			sprintf(tag, "%02d", sign + 1);

			m_top->addChild("tag", tag, (int)strlen(tag) + 1);
		}
		return true;
	}
};

#endif
