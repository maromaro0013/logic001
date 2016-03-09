// 2014-12-29 y_ohta

/*-----------------------------------------------------------------------------
 *  planet sign
 *	指定された天体のサインを求める(7パターン/12パターン/選択可能版)
 *
 *	必要なパラメータ
 *	bymd1:生年月日(yyyymmdd形式)
 *	bhms1:生時分秒(hhmmss形式)
 *	bpref1:出生地(都道府県コード)
 *
 *	bymd2:相手生年月日(yyyymmdd形式)
 *	bhms2:相手生時分秒(hhmmss形式)
 *	bpre2:相手出生地(都道府県コード)
 *
 *	ymd:生年月日(yyyymmdd形式)
 *	hms:生時分秒(hhmmss形式)
 *	pref:出生地(都道府県コード)
 *
 *	planetId1:見たい天体(0-10)
 *	scope1：見たいホロスコープ1(natal1:あなたネータル natal2:相手ネータル transit:トランジット 指定なし：あなたネータル)
 *	code_pattern：原稿コードのパターン数(7→7パターン　6→6パターン　6,7以外、もしくは指定なし→12パターン)
 *----------------------------------------------------------------------------*/

#ifndef _PLANETSIGN003_HPP_
#define _PLANETSIGN003_HPP_

#include "../actionBase.hpp"

#include "../../core/japanCoordinate.hpp"

#include "../../logicCore/astrology/aspect.hpp"
#include "../../logicCore/astrology/horoscope.hpp"
#include "../../logicCore/astrology/astrologyUtil.hpp"

#include "../../logicCore/astrology/builder/houseSetBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeImageBuilder.hpp"

class planetSign003 : public actionBase {
private:
	astrologyHoroscope*					m_natal;
	astrologyHoroscope*					m_natal2;
	astrologyHoroscope*					m_transit;

	int									m_planetId1;
	int									m_code_pattern;

public:
	planetSign003() {
		m_natal = NULL;
		m_natal2 = NULL;
		m_transit = NULL;
	}
	~planetSign003() {
		if (m_natal != NULL) {
			delete m_natal;
		}
		if (m_natal2 != NULL) {
			delete m_natal2;
		}
		if (m_transit != NULL) {
			delete m_transit;
		}
	}

	bool ParseRequest(requestFormatter* request) {
		if (request->getIntParam("scope1") == cREQUEST_PARAM_ERROR) {
			return false;
		}

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

		horoscopeBuilder* hBuilder = new horoscopeBuilder();
		// build natal horoscope
		{
			hBuilder->setDateTime(request->getBymd1());
			hBuilder->setLatitude(japanCoodinate::getLatitudeFromId(bpref1));
			hBuilder->setLongitude(japanCoodinate::getLongitudeFromId(bpref1));
			m_natal = hBuilder->generate();
		}

		if (request->getIntParam("bymd2") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("bhms2") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		int bpref2 = request->getIntParam("bpref2");
		if (bpref2 == cREQUEST_PARAM_ERROR) {
			return false;
		}
		// build natal2 horoscope
		{
			hBuilder->setDateTime(request->getBymd2());
			hBuilder->setLatitude(japanCoodinate::getLatitudeFromId(bpref2));
			hBuilder->setLongitude(japanCoodinate::getLongitudeFromId(bpref2));
			m_natal2 = hBuilder->generate();
		}

		if (request->getIntParam("ymd") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("hms") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		int pref = request->getIntParam("pref");
		if (pref == cREQUEST_PARAM_ERROR) {
			return false;
		}
		// build transit horoscope
		{
			hBuilder->setDateTime(request->getYmd());
			hBuilder->setLatitude(japanCoodinate::getLatitudeFromId(pref));
			hBuilder->setLongitude(japanCoodinate::getLongitudeFromId(pref));
			m_transit = hBuilder->generate();
		}

		delete hBuilder;

		return true;
	}

	bool Run(requestFormatter* request) {
		char data[0xffff];
		char scope1[256];

		request->getStringParam("scope1", scope1);
		formatterBase* myProf = m_top->addChild("myProf", NULL, 0);

		astrologyHoroscope* scope;
		// 相手ネータル
		if (strcmp(scope1, "natal2") == 0) {
			scope = m_natal2;
		}
		// トランジット
		else if (strcmp(scope1, "transit") == 0) {
			scope = m_transit;
		}
		// あなたネータル
		else {
			scope = m_natal;
		}
		// natal/natal2/transit horoscope
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
			scope->printPlanetLongitude(data, sizeof(data));
			planetState->addChild("planet", data, (int)strlen(data) + 1);
			
			scope->printPlanetSign(data, sizeof(data));
			planetState->addChild("sign", data, (int)strlen(data) + 1);
			
			scope->printPlanetHouse(data, sizeof(data));
			planetState->addChild("house", data, (int)strlen(data) + 1);
			// ------------------
			
			// ------------------
			formatterBase* houseState = horoscope->addChild("houseState", NULL, 0);
			int asc = scope->getAscendant();
			sprintf(data, "%s", astrologySign::getJpSignName(asc));
			houseState->addChild("asc", data, (int)strlen(data) + 1);
			
			int mc = scope->getMC();
			sprintf(data, "%s", astrologySign::getJpSignName(mc));
			houseState->addChild("mc", data, (int)strlen(data) + 1);
			
			scope->printHouseCusp(data, sizeof(data));
			houseState->addChild("houseCusp", data, (int)strlen(data) + 1);
			// ------------------
		}

		// tag
		{
			int sign = scope->getPlanetSet()->getPlanet(m_planetId1)->getSign()->getSign();
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
