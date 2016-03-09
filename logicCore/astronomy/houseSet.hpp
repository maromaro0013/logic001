// 2014-11-07 y_ohta

#ifndef _HOUSESET_HPP_
#define _HOUSESET_HPP_

#include "house.hpp"

class astrologyHouseSet {
private:
	astrologyHouse*		m_houseArr[cHOUSE_MAX];
	
public:
	astrologyHouseSet() {
		for (int i = 0; i < cHOUSE_MAX; i++) {
			m_houseArr[i] = new astrologyHouse();
			m_houseArr[i]->setHouse(i);
		}
	}
	~astrologyHouseSet() {
		for (int i = 0; i < cHOUSE_MAX; i++) {
			delete m_houseArr[i];
		}
	}

	astrologyHouse* getHouse(int idx) const{
		if (idx < cHOUSE_MAX) {
			return m_houseArr[idx];
		}
		return m_houseArr[0];
	}

	astrologyHouse* getHouseOfDegree(double degree) {
		for (int i = 0; i < cHOUSE_MAX; i++) {
			astrologyHouse* tmp = m_houseArr[i];
			double houseCusp1 = tmp->getCuspLongitude();

			int next = (i + 1)%cHOUSE_MAX;
			astrologyHouse* nextHouse = m_houseArr[next];
			double houseCusp2 = nextHouse->getCuspLongitude();

			if (houseCusp1 < houseCusp2) {
				if (houseCusp1 <= degree && degree < houseCusp2) {
					return tmp;
				}
			}
			else {
				if (houseCusp1 <= degree || degree < houseCusp2) {
					return tmp;
				}
			}
		}

		return NULL;
	}
};

#endif
