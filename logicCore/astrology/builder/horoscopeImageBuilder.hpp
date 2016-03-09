// 2014-12-8 y_ohta

#ifndef _HOROSCOPEIMAGEBUILDER_HPP_
#define _HOROSCOPEIMAGEBUILDER_HPP_

#include "../../astronomy/houseSet.hpp"
#include "../../astronomy/planetSet.hpp"
#include "../horoscope.hpp"
#include "houseSetBuilder.hpp"

class horoscopeImageBuilder {
private:
	int						m_asc_sign;
	int						m_xCoordinate[ePLANET_MAX];
	int						m_yCoordinate[ePLANET_MAX];

public:
	horoscopeImageBuilder() {
	}
	~horoscopeImageBuilder() {
	}

	void PrintBase(char* buff, int length) {
		int v = m_asc_sign + ePLANET_MAX;
		v = (v - 1) % 12 + 1;
		sprintf(buff, "%02d", v);
	}
	void PrintPlanetX(char* buff, int length) {
		sprintf(buff, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				m_xCoordinate[0],
				m_xCoordinate[1],
				m_xCoordinate[2],
				m_xCoordinate[3],
				m_xCoordinate[4],
				m_xCoordinate[5],
				m_xCoordinate[6],
				m_xCoordinate[7],
				m_xCoordinate[8],
				m_xCoordinate[9]);
	}
	void PrintPlanetY(char* buff, int length) {
		sprintf(buff, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				m_yCoordinate[0],
				m_yCoordinate[1],
				m_yCoordinate[2],
				m_yCoordinate[3],
				m_yCoordinate[4],
				m_yCoordinate[5],
				m_yCoordinate[6],
				m_yCoordinate[7],
				m_yCoordinate[8],
				m_yCoordinate[9]);
	}

	void convertCoordinate(astrologyHoroscope* horoscope) {
		astrologyPlanetSet* planetSet = horoscope->getPlanetSet();

		m_asc_sign = horoscope->getAscendant();
		double ascSignLongitude = m_asc_sign * 30.0f;

		// 仮想座標系の定義
		const int x0 = 512;
		const int y0 = 512;
		const int r0 = 352;
		const int rd =  64;
		const int wd = 128;

		// 接近している天体数を数える
		int qtyClosedPlanets[ePLANET_MAX];
		int maxQty = -1;
		for(int i = 0; i < ePLANET_MAX; i++) {
			double baseLongitude = planetSet->getPlanet(i)->getLongitude();
			qtyClosedPlanets[i] = 0;

			for (int j = i + 1; j < ePLANET_MAX; j++) {
				double targetLongitude = planetSet->getPlanet(j)->getLongitude();
				if(this->calculateAbsoluteAngularDifference(baseLongitude, targetLongitude) < 30.0 ){
					qtyClosedPlanets[i]++;
				}
			}
			// 最大接近数をカウントする
			if (qtyClosedPlanets[i] > maxQty) {
				maxQty = qtyClosedPlanets[i];
			}
		}

		// 最大接近数を基準に半径を微調整する
		double rad[ePLANET_MAX];
		for(int i = 0; i < ePLANET_MAX; i++) {
			double ratio = (double)qtyClosedPlanets[i] / (double)maxQty;
			rad[i] = r0 - (int)(rd * 3.0 * ratio);
		}

		// 半径と角度から座標を計算する
		for(int i = 0; i < ePLANET_MAX; i++ ){
			double longitude = planetSet->getPlanet(i)->getLongitude();
			double lambda = (longitude - ascSignLongitude) - 195.0;
			if(lambda < 0.0){
				lambda += 360.0;
			}

			double radLambda = deg2rad(lambda);
			double glyphWidth = wd * rad[i] / r0;
			double x = x0 + rad[i] * cos(radLambda) - glyphWidth / 2;
			double y = y0 - rad[i] * sin(radLambda) - glyphWidth / 2;

			m_xCoordinate[i] = (int)x;
			m_yCoordinate[i] = (int)y;
		}
	}

private:
	// 離角を[-180.0, +180.0)の範囲で計算する
	double calculateAngularDifference(double baseLongitude, double targetLongitude ){
		double diffAngle = targetLongitude - baseLongitude;
		if( diffAngle > +180.0 ){
			diffAngle -= 360.0;
		}
		else if(diffAngle < -180.0){
			diffAngle += 360.0;
		}
		return diffAngle;
	}

	// 離角を[0.0, +180.0]の範囲で計算する
	double calculateAbsoluteAngularDifference(double baseLongitude, double targetLongitude ){
		return fabs( this->calculateAngularDifference(baseLongitude, targetLongitude));
	}
};

#endif
