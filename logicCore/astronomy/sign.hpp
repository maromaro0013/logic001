// 2014-11-07 y_ohta

#ifndef _SIGN_HPP_
#define _SIGN_HPP_

// astorological sign
enum {
	eASTROLOGICALSIGN_ARIES = 0,
	eASTROLOGICALSIGN_TAURUS = 1,
	eASTROLOGICALSIGN_GEMINI = 2,
	eASTROLOGICALSIGN_CANCER = 3,
	eASTROLOGICALSIGN_LEO = 4,
	eASTROLOGICALSIGN_VIRGO = 5,
	eASTROLOGICALSIGN_LIBRA = 6,
	eASTROLOGICALSIGN_SCORPIO = 7,
	eASTROLOGICALSIGN_SAGITTARIUS = 8,
	eASTROLOGICALSIGN_CAPRICORN = 9,
	eASTROLOGICALSIGN_AQUARIUS = 10,
	eASTROLOGICALSIGN_PISCES = 11,
	eASTROLOGICALSIGN_MAX
};

// polarity
enum {
	ePOLARITY_MALE = 0,
	ePOLARITY_FEMALE = 1,
	ePOLARITY_MAX
};

// quality
enum {
	eQUALITY_CARDINAL = 0,
	eQUALITY_FIXED = 1,
	eQUALITY_MUTABLE = 2,
	eQUALITY_MAX
};

// element
enum {
	eELEMENT_FIRE = 0,
	eELEMENT_EARTH = 1,
	eELEMENT_AIR = 2,
	eELEMENT_WATER = 3,
	eELEMENT_MAX
};

class astrologySign {
private:
	int		m_sign;
	int		m_quality;
	int		m_polarity;
	int		m_element;

public:
	astrologySign() {
		m_sign = 0;
		m_quality = 0;
		m_polarity = 0;
		m_element = 0;
	}
	~astrologySign() {
		
	}

	void setSign(int sign) {
		m_sign = sign;
		m_polarity = sign%ePOLARITY_MAX;
		m_quality = sign%eQUALITY_MAX;
		m_element = sign%eELEMENT_MAX;
	}

	int getSign() const{
		return m_sign;
	}
	int getPolarity() const{
		return m_polarity;
	}
	int getQuality() const{
		return m_quality;
	}
	int getElement() const{
		return m_element;
	}

	static const char* getEnSignName(int sign) {
		static const char names[eASTROLOGICALSIGN_MAX][16] = {
			"ARIES",
			"TAURUS",
			"GEMINI",
			"CANCER",
			"LEO",
			"VIRGO",
			"LIBRA",
			"SCORPIO",
			"SAGITTARIUS",
			"CAPRICORN",
			"AQUARIUS",
			"PISCES"
		};

		if (sign < eASTROLOGICALSIGN_MAX) {
			return names[sign];
		}
		return names[0];
	}

	static const char* getJpSignName(int sign) {
		static const char names[eASTROLOGICALSIGN_MAX][16] = {
			"牡羊座",
			"牡牛座",
			"双子座",
			"蟹座",
			"獅子座",
			"乙女座",
			"天秤座",
			"蠍座",
			"射手座",
			"山羊座",
			"水瓶座",
			"魚座"
		};
		
		if (sign < eASTROLOGICALSIGN_MAX) {
			return names[sign];
		}
		return names[0];
	}

	static int getSignFromLongitude(double longitude) {
		return (int)(longitude / 30.0);
	}
};

#endif

