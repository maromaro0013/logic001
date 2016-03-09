#ifndef _TIMINGFORTUNEBASE_HPP_
#define _TIMINGFORTUNEBASE_HPP_

#define cTIMINGFORTUNE_TARGETASPECTS_MAX		(8)

#include "../actionBase.hpp"

#include "../../core/japanCoordinate.hpp"

#include "../../logicCore/astrology/aspect.hpp"
#include "../../logicCore/astrology/horoscope.hpp"
#include "../../logicCore/astrology/astrologyUtil.hpp"

#include "../../logicCore/astrology/builder/houseSetBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeBuilder.hpp"
#include "../../logicCore/astrology/builder/horoscopeImageBuilder.hpp"

class timingFortuneBase : public actionBase {
protected:
	int						m_aspectCount;
	astrologyAspect*		m_targetAspects[cTIMINGFORTUNE_TARGETASPECTS_MAX];
	horoscopeBuilder*		m_hBuilder;

public:
	timingFortuneBase() {
		m_aspectCount = 0;
		for (int i = 0; i < cTIMINGFORTUNE_TARGETASPECTS_MAX; i++) {
			m_targetAspects[i] = NULL;
		}
		m_hBuilder = new horoscopeBuilder();
	}
	virtual ~timingFortuneBase() {
		for (int i = 0; i < cTIMINGFORTUNE_TARGETASPECTS_MAX; i++) {
			if (m_targetAspects[i] != NULL) {
				delete m_targetAspects[i];
			}
			m_targetAspects[i] = NULL;
		}
		if (m_hBuilder != NULL) {
			delete m_hBuilder;
			m_hBuilder = NULL;
		}
	}

public:
	void addAspect(int aspect) {
		if (m_aspectCount < cTIMINGFORTUNE_TARGETASPECTS_MAX) {
			m_targetAspects[m_aspectCount] = new astrologyAspect();
			m_targetAspects[m_aspectCount]->setValue(aspect);
		}
		m_aspectCount++;
	}

	bool matchAspects(double delta, double orb) {
		for (int i = 0; i < m_aspectCount; i++) {
			if (m_targetAspects[i]->match(delta, orb)) {
				return true;
			}
		}
		return false;
	}

	bool validate(requestFormatter* request) {
		if (request->getIntParam("bymd1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("bhms1") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		if (request->getIntParam("ymd") == cREQUEST_PARAM_ERROR) {
			return false;
		}
		return true;
	}
};

#endif
