// 2014-12-29 y_ohta

#ifndef _ASPECT_HPP_
#define _ASPECT_HPP_

#include <math.h>
#include "astrologyUtil.hpp"

// aspect name
enum {
	eASPECT_NONE = -1,
	eASPECT_CONJUNCTION = 0,
	eASPECT_SEXTILE = 1,
	eASPECT_SQUARE = 2,
	eASPECT_TRINE = 3,
	eASPECT_OPPOSITION = 4,
	eASPECT_INCONJUNCT = 5,
	eASPECT_QUINCUNX = 6,
	eASPECT_SEMISEXTILE = 7,
	eASPECT_SEMISQUARE = 8,
	eASPECT_SESQUIQUADRATE = 9,
	eASPECT_SEMIQUINTILE = 10,
	eASPECT_QUINTILE = 11,
	eASPECT_BIQUINTILE = 12,
	eASPECT_SEPTILE = 13,
	eASPECT_MAX = eASPECT_SEPTILE + 1
};

class astrologyAspect {
private:
	int				m_value;
	float			m_angle;
	float			m_orb;

public:
	astrologyAspect() {
		m_value = 0;
		m_angle = 0.0f;
		m_orb = 0.0f;
	}
	~astrologyAspect() {
	}

	void setAngle(float angle, float orb) {
		m_angle = fabsf(angle);
		while (m_angle > 180.0f) {
			m_angle = 360.0f - m_angle;
		}

		m_orb = orb;

		m_value = eASPECT_NONE;
		for (int i = eASPECT_CONJUNCTION; i < eASPECT_MAX; i++) {
			float a_angle = astrologyAspect::getAngleFromAspect(i);
			if (fabsf(a_angle - angle) <= orb) {
				m_value = i;
				break;
			}
		}
	}

	void setValue(int aspect) {
		if (aspect < eASPECT_MAX && aspect > 0) {
			m_value = aspect;
		}
		m_angle = astrologyAspect::getAngleFromAspect(aspect);
	}

	bool isMajor(void) {
		if (m_value >= eASPECT_CONJUNCTION && m_value <= eASPECT_OPPOSITION) {
			return true;
		}
		return false;
	}

	static float getAngleFromAspect(int aspect) {
		float arr[eASPECT_MAX] = {
			0.0f,
			60.0f,
			90.0f,
			120.0f,
			180.0f,
			150.0f,
			150.0f,
			30.0f,
			45.0f,
			135.0f,
			36.0f,
			72.0f,
			144.0f,
			51.428571f,
		};

		if (aspect < eASPECT_MAX && aspect > 0) {
			return arr[aspect];
		}
		return arr[0];
	}

	bool match (double delta, double orb) {
		delta = astrologyUtil::degree_normalize(delta);
		if (fabs(delta - m_angle) < orb) {
			return true;
		}
		return false;
	}
};

#endif
