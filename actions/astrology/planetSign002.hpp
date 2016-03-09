// 2014-12-29 y_ohta

/*-----------------------------------------------------------------------------
 *  planet sign
 *	指定された天体のサインを求める(7パターン/12パターン/選択可能版)
 *
 *	必要なパラメータ
 *	bymd1:生年月日(yyyymmdd形式)
 *	bhms1:生時分秒(hhmmss形式)
 *	bpref1:出生地(都道府県コード)
 *	planetId1:見たい天体(0-10)
 *	code_pattern：原稿コードのパターン数(7→7パターン　6→6パターン　6,7以外、もしくは指定なし→12パターン)
 *----------------------------------------------------------------------------*/

#ifndef _PLANETSIGN002_HPP_
#define _PLANETSIGN002_HPP_

#include "../actionBase.hpp"

#include "../../core/japanCoordinate.hpp"

#include "../../logicCore/astrology/aspect.hpp"
#include "../../logicCore/astrology/horoscope.hpp"
#include "../../logicCore/astrology/astrologyUtil.hpp"

#include "../../logicCore/astrology/builder/houseSetBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeImageBuilder.hpp"

class planetSign002 : public actionBase {
private:
	astrologyHoroscope*					m_natal;
	int									m_planetId1;

	int									m_code_pattern;

public:
	planetSign002() {
		m_natal = NULL;
	}
	~planetSign002() {
		if (m_natal != NULL) {
			delete m_natal;
		}
	}

	bool ParseRequest(requestFormatter* request) {
		m_code_pattern = request->getIntParam("code_pattern");
		if (m_code_pattern == cREQUEST_PARAM_ERROR) {
			return false;
		}

		if (request->getIntParam("bymd1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("bhms1") == cREQUEST_PARAM_ERROR) {
			return false;
		}

		m_planetId1 = request->getIntParam("planetId1");
		if (m_planetId1 == cREQUEST_PARAM_ERROR) {
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
			int sign = m_natal->getPlanetSet()->getPlanet(m_planetId1)->getSign()->getSign();
			char tagstr[0xff];
			int tag = sign + 1;

			//code_pattern
			if (m_code_pattern == 7) {
				if(tag == 1 || tag == 5){
					tag = 1;
				}
				else if(tag == 2 || tag == 7){
					tag = 2;
				}
				else if(tag == 3 || tag == 6){
					tag = 3;
				}
				else if(tag == 4 || tag == 8){
					tag = 4;
				}
				else if(tag == 9 || tag == 12){
					tag = 5;
				}
				else if(tag == 10){
					tag = 6;
				}
				else if(tag == 11){
					tag = 7;
				}
			}
			else if (m_code_pattern == 6) {
				if(tag == 1 || tag == 7){
					tag = 1;
				}
				else if(tag == 4 || tag == 10){
					tag = 2;
				}
				else if(tag == 5 || tag == 11){
					tag = 3;
				}
				else if(tag == 2 || tag == 3){
					tag = 4;
				}
				else if(tag == 3 || tag == 9){
					tag = 5;
				}
				else if(tag == 6 || tag == 12){
					tag = 6;
				}
			}

			sprintf(tagstr, "%02d", tag);

			m_top->addChild("tag", tagstr, (int)strlen(tagstr) + 1);
		}
		return true;
	}
};

#endif
