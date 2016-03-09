// 2014-12-29 y_ohta

#ifndef _ASTROLOGYUTIL_HPP_
#define _ASTROLOGYUTIL_HPP_

class astrologyUtil {
public:
	static double calcMidPoint(double degree1, double degree2) {
		double small = degree1;
		double big = degree2;

		if (degree1 > degree2) {
			small = degree2;
			big = degree1;
		}

		double delta = fabs(degree1 - degree2);
		double baseDegree = small;

		if (delta > 180.0) {
			delta = 360.0 - delta;
			baseDegree = big;
		}
		else if (delta == 180.0) {
			if (small >= 90.0) {
				baseDegree = big;
			}
		}

		return degree_normalize(baseDegree + (delta / 2.0));
	}

	static double degree_normalize(double degree) {
		if (degree < 0.0) {
			double angle1 = -degree;
			double angle2 = (int) (angle1 / 360.0);

			angle1 -= 360.0 * angle2;
			double ret = 360.0 - angle1;
			if (ret >= 360) {
				ret -= 360;
			}
			return ret;
		}
		else if (degree >= 360.0) {
			int n = (int) (degree / 360.0);
			return degree - 360.0 * n;
		}
		
		return degree;
	}

	static double degree_diffNormalize(double angle) {
		double v = degree_normalize(angle);
		if (v >= 180.0) {
			return 360 - v;
		}
		
		return v;
	}
};

#endif
