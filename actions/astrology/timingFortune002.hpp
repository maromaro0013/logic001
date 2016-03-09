// 2014-12-30 y_ohta

/*-----------------------------------------------------------------------------
 *  時期運
 *	ネータルチャートのハウスの支配星とトランジットチャートの天体角度が、0,120,240度を組んでいる時の期間を求める
 *	アスペクトを組んでいる期間のトランジットチャートの天体がどのネータルハウスにいるかを求める
 *
 *	必要なパラメータ
 *	bymd1:生年月日(yyyymmdd形式)
 *	bhms1:生時分秒(hhmmss形式)
 *	bpref1:出生地(都道府県コード)
 *
 *	ymd:生年月日(yyyymmdd形式)
 *
 *	houseId:見たいハウス(1-12)
 *	planetId:見たい天体(0-10)
 *	pattern:原稿パターンを増やすか 0:増やさない(12パターン) 1:増やす(24パターン)
 *----------------------------------------------------------------------------- */

#ifndef _TIMINGFORTUNE002_HPP_
#define _TIMINGFORTUNE002_HPP_

#include "../astrologyBase/timingFortuneBase.hpp"

class timingFortune002 : public timingFortuneBase {
private:
	astrologyHoroscope*					m_natal;
	astrologyHoroscope*					m_transit;
	
	int									m_planetId;
	int									m_houseId;
	int									m_pattern;

public:
	timingFortune002() {
		m_natal = NULL;
		m_transit = NULL;
	}
	~timingFortune002() {
		if (m_natal != NULL) {
			delete m_natal;
		}
		if (m_transit) {
			delete m_transit;
		}
	}

	bool ParseRequest(requestFormatter* request) {
		if (this->validate(request) == false) {
			return false;
		}
		m_houseId = request->getIntParam("houseId");
		if (m_houseId == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (m_houseId < 1 || m_houseId > 12) {
			return false;
		}
		m_houseId -= 1;

		m_planetId = request->getIntParam("planetId");
		if (m_planetId == cREQUEST_PARAM_ERROR) {
			return false;
		}

		int bpref1 = request->getIntParam("bpref1");
		if (bpref1 == cREQUEST_PARAM_ERROR) {
			return false;
		}

		m_pattern = request->getIntParam("pattern");
		if (m_pattern == cREQUEST_PARAM_ERROR) {
			return false;
		}

		// natal
		m_hBuilder->setDateTime(request->getBymd1());
		m_hBuilder->setLatitude(japanCoodinate::getLatitudeFromId(bpref1));
		m_hBuilder->setLongitude(japanCoodinate::getLongitudeFromId(bpref1));
		m_natal = m_hBuilder->generate();

		// transit
		int pref = ePREFNAME_NARA;
		m_hBuilder->setDateTime(request->getYmd());
		m_hBuilder->setTime(12, 0, 0);
		m_hBuilder->setLatitude(japanCoodinate::getLatitudeFromId(pref));
		m_hBuilder->setLongitude(japanCoodinate::getLongitudeFromId(pref));
		m_transit = m_hBuilder->generate();

		return true;
	}

	bool Run(requestFormatter* request) {
		astrologyPlanetSet* natalPlanetSet = m_natal->getPlanetSet();
		astrologyHouseSet* natalHouseSet = m_natal->getHouseSet();
		double houseLongitude = natalHouseSet->getHouse(m_houseId)->getCuspLongitude();
		int sign = astrologySign::getSignFromLongitude(houseLongitude);
		int ruler = astrologyPlanet::getRulerFromSign(sign, false);

		this->addAspect(eASPECT_CONJUNCTION);
		this->addAspect(eASPECT_TRINE);

		// dafault pref
		int pref = ePREFNAME_NARA;

		// orb
		double orb = 1.0f;
		if (m_planetId == ePLANET_MOON) {
			orb = 15.0;
		}

		// 支配星の度数を取得
		double rulerDegree = natalPlanetSet->getPlanet(ruler)->getLongitude();
		double latitude = japanCoodinate::getLatitudeFromId(pref);
		double longitude = japanCoodinate::getLongitudeFromId(pref);

		// transit horoscope
		m_hBuilder->setDateTime(request->getYmd());
		m_hBuilder->setTime(12, 0, 0);
		m_hBuilder->setLongitude(longitude);
		m_hBuilder->setLatitude(latitude);
		astrologyHoroscope* transitHoroscope = m_hBuilder->generate();

		// aspect search
		for (int i = 0; i < 1000; i++) {
			m_hBuilder->generate(transitHoroscope);
			astrologyPlanetSet* transitPlanetSet = transitHoroscope->getPlanetSet();
			double delta = transitPlanetSet->getPlanet(m_planetId)->getLongitude() - rulerDegree;

			if (this->matchAspects(delta, orb)) {
				break;
			}
			m_hBuilder->addDays(1);
		}

		// ymd
		char str[512];
		formatterBase* transit = m_top->addChild("transit", NULL, 0);
		formatterBase* datePref = transit->addChild("datePref", NULL, 0);
		Date* ymd = request->getYmd();
		sprintf(str, "%04d%02d%02d", ymd->getYear(), ymd->getMonth(), ymd->getDay());
		datePref->addChild("ymd", str, (int)strlen(str) + 1);

		// tag
		double transitLongitude = transitHoroscope->getPlanetSet()->getPlanet(m_planetId)->getLongitude();
		astrologyHouse* house = natalHouseSet->getHouseOfDegree(transitLongitude);
		sprintf(str, "%02d", house->getHouse() + 1);
		// add pattern
		if (m_pattern == 1) {
			double jd = transitHoroscope->getJulianDay();
			int v = (int)jd % 2 + 1;
			char addtag[32];
			sprintf(addtag, "%d", v);
			strcat(str, addtag);
		}
		m_top->addChild("tag", str, (int)strlen(str) + 1);

		// startDate
		const JulianDate* date = m_hBuilder->getDate();
		sprintf(str, "%04d%02d%02d", date->getYear(), date->getMonth(), date->getDay());
		m_top->addChild("startDate", str, (int)strlen(str) + 1);

		delete transitHoroscope;

		return true;
	}
};

#endif
