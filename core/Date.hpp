// 2014-12-29 y_ohta

#ifndef _DATE_HPP_
#define _DATE_HPP_

#include <time.h>

class Date {
protected:
	int		m_year;
	int		m_month;
	int		m_day;

	int		m_hour;
	int		m_min;
	int		m_sec;

public:
	Date() {
		m_year = 0;
		m_month = 0;
		m_day = 0;

		m_hour = 0;
		m_min = 0;
		m_sec = 0;
	}
	~Date() {
	}

	int getYear(void) const {
		return m_year;
	}
	int getMonth(void) const {
		return m_month;
	}
	int getDay(void) const {
		return m_day;
	}

	int getHour(void) const {
		return m_hour;
	}
	int getMin(void) const {
		return m_min;
	}
	int getSec(void) const {
		return m_sec;
	}

	void setDate(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
	}

	void addDays(int days) {
		if (days > 0) {
			int monthDays = Date::getDaysFromMonth(m_year, m_month);
			if ((m_day + days) > monthDays) {
				if (m_month + 1 > 12) {
					m_month = 1;
					m_year++;
				}
				else {
					m_month++;
				}
				int diff = monthDays - m_day + 1;
				m_day = 1;
				this->addDays(days - diff);
			}
			else {
				m_day += days;
			}
		}
	}

	void subDays(int days) {
		if (days > 0) {
			if ((m_day - days) <= 0) {
				if (m_month - 1 <= 0) {
					m_month = 12;
					m_year--;
				}
				else {
					m_month--;
				}
				int diff = m_day;
				m_day = Date::getDaysFromMonth(m_year, m_month);
				this->subDays(days - diff);
			}
			else {
				m_day -= days;
			}
		}
	}

	void setTime(int hour, int min, int sec) {
		m_hour = hour;
		m_min = min;
		m_sec = sec;
	}

	void setNowDate() {
		time_t tmp = time(NULL);
		tm tmp_tm = *localtime(&tmp);

		m_year = tmp_tm.tm_year + 1900;
		m_month = tmp_tm.tm_mon + 1;
		m_day = tmp_tm.tm_mday;

		m_hour = tmp_tm.tm_hour;
		m_min = tmp_tm.tm_min;
		m_sec = tmp_tm.tm_sec;
	}

	static int getDaysFromMonth(int year, int month) {
		if (month <= 0 || month > 12) {
			return 0;
		}

		static const int days[12] = {
			31,
			28,
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31,
		};

		int ret = days[month - 1];
		if (month == 2) {
			if ((year%4 == 0 && year%100 != 0) || year%400 == 0) {
				ret += 1;
			}
		}
		return ret;
	}

	void printDate() const {
		char buf[512];
		sprintf(buf, "%d-%d-%d %d:%d:%d", m_year, m_month, m_day, m_hour, m_min, m_sec);
		printf("%s\n", buf);
	}
};

#endif
