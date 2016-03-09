// 2014-11-07 y_ohta

#ifndef _HOUSE_HPP_
#define _HOUSE_HPP_

#define cHOUSE_MAX (12)

class astrologyHouse {
private:
	int		m_house;
	double	m_cuspLongitude;
	
public:
	astrologyHouse() {
	}
	~astrologyHouse() {
	}

	int getHouse(void) {
		return m_house;
	}
	void setHouse(int house) {
		m_house = house;
	}

	void setCuspLongitude(double cuspLongitude) {
		m_cuspLongitude = cuspLongitude;
	}
	double getCuspLongitude(void) const{
		return m_cuspLongitude;
	}
};

#endif
