// 2015-01-06 y_ohta

/*-----------------------------------------------------------------------------
 *  時期運
 *	30日間でネータル水星+トランジット月が120度アスペクトする日
 *
 *	必要なパラメータ
 *	bymd1:生年月日(yyyymmdd形式)
 *	bhms1:生時分秒(hhmmss形式)
 *	bpref1:出生地(都道府県コード)
 *	ymd:トランジット年月日(yyyymmdd形式)
 *----------------------------------------------------------------------------- */

#ifndef _TIMINGFORTUNE012_HPP_
#define _TIMINGFORTUNE012_HPP_

#include "../astrologyBase/timingFortuneBase.hpp"

class timingFortune012 : public timingFortuneBase {
private:
	astrologyHoroscope*					m_natal;
	astrologyHoroscope*					m_transit;
	
public:
	timingFortune012() {
		m_natal = NULL;
		m_transit = NULL;
	}
	~timingFortune012() {
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
		
		int bpref1 = request->getIntParam("bpref1");
		if (bpref1 == cREQUEST_PARAM_ERROR) {
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
		int planet1 = ePLANET_MERCURY;
		int planet2 = ePLANET_MOON;
		int aspectDays[60];
		int aspectDaysCount;

		// 指定天体の度数を取得
		double planetDegree = m_natal->getPlanetSet()->getPlanet(planet1)->getLongitude();

//		astrologyPlanetSet* natalPlanetSet = m_natal->getPlanetSet();
//		astrologyHouseSet* natalHouseSet = m_natal->getHouseSet();
		
		this->addAspect(eASPECT_TRINE);
		
		// dafault pref
		int pref = ePREFNAME_NARA;
		double latitude = japanCoodinate::getLatitudeFromId(pref);
		double longitude = japanCoodinate::getLongitudeFromId(pref);
		
		// orb (moon)
		double orb = 15.0;

		// transit horoscope
		m_hBuilder->setDateTime(request->getYmd());
		m_hBuilder->setTime(12, 0, 0);
		m_hBuilder->setLongitude(longitude);
		m_hBuilder->setLatitude(latitude);
		astrologyHoroscope* transitHoroscope = m_hBuilder->generate();

		// orbの設定で近い日が重なるので、30日前から10日進めて検索する
		m_hBuilder->subDays(30);

		// aspect search
		aspectDaysCount = 0;
		for (int i = 0; i < 60; i++) {
			m_hBuilder->generate(transitHoroscope);
			astrologyPlanetSet* transitPlanetSet = transitHoroscope->getPlanetSet();
			double delta = astrologyUtil::degree_diffNormalize(transitPlanetSet->getPlanet(planet2)->getLongitude() - planetDegree);
	
			if (this->matchAspects(delta, orb)) {
				if (i >= 30) {
					aspectDays[aspectDaysCount] = i - 30;
					aspectDaysCount++;
				}
				m_hBuilder->addDays(9);
				i += 9;
			}
			m_hBuilder->addDays(1);
		}

		m_hBuilder->setDateTime(request->getYmd());
		m_hBuilder->setTime(12, 0, 0);

		if (aspectDaysCount > 0) {
			char str[512];
			// 最初に見つかった日付をトランジットの日とする
			m_hBuilder->addDays(aspectDays[0]);
			m_hBuilder->generate(transitHoroscope);
			// tag
			astrologyHouse* house = transitHoroscope->getPlanetSet()->getPlanet(planet2)->getHouse();
			sprintf(str, "%02d", house->getHouse() + 1);
			m_top->addChild("tag", str, (int)strlen(str) + 1);

			// startDate
			const JulianDate* date = m_hBuilder->getDate();
			sprintf(str, "%04d%02d%02d", date->getYear(), date->getMonth(), date->getDay());

			for (int i = 1; i < aspectDaysCount; i++) {
				m_hBuilder->setDateTime(request->getYmd());
				m_hBuilder->addDays(aspectDays[i]);
				const JulianDate* transit_date = m_hBuilder->getDate();
				char date_str[512];

				sprintf(date_str, ",%04d%02d%02d", transit_date->getYear(), transit_date->getMonth(), transit_date->getDay());
				strcat(str, date_str);
			}
			m_top->addChild("startDate", str, (int)strlen(str) + 1);
		}

		delete transitHoroscope;
		
		return true;
	}
};

#endif
