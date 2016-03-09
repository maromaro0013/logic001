// 2015-01-06 y_ohta

#ifndef _ACTIONMETHOD_HPP_
#define _ACTIONMETHOD_HPP_

#include "astrology/dailySign001.hpp"
#include "astrology/timingFortune001.hpp"
#include "astrology/timingFortune002.hpp"
#include "astrology/timingFortune003.hpp"
#include "astrology/timingFortune004.hpp"
#include "astrology/timingFortune005.hpp"
#include "astrology/timingFortune006.hpp"
#include "astrology/timingFortune012.hpp"
#include "astrology/planetSign001.hpp"
#include "astrology/planetSign002.hpp"
#include "astrology/planetSign003.hpp"

#define cACTIONMETHOD_NAME_MAX		(256)

// logics
enum {
	eACTIONMETHOD_DAILYSIGN001 = 0,
	eACTIONMETHOD_TIMINGFORTUNE001,
	eACTIONMETHOD_TIMINGFORTUNE002,
	eACTIONMETHOD_TIMINGFORTUNE003,
	eACTIONMETHOD_TIMINGFORTUNE004,
	eACTIONMETHOD_TIMINGFORTUNE005,
	eACTIONMETHOD_TIMINGFORTUNE006,
	eACTIONMETHOD_TIMINGFORTUNE012,
	eACTIONMETHOD_PLANETSIGN001,
	eACTIONMETHOD_PLANETSIGN002,
	eACTIONMETHOD_PLANETSIGN003,

	eACTIONMETHOD_MAX
};

class actionMethod {
private:
	actionBase*			m_action;
	requestFormatter*	m_request;
	
public:
	actionMethod() {
		m_action = NULL;
		m_request = NULL;
	}
	~actionMethod() {
		this->deleteMethod();
	}

	static int getMethodId(const char* name) {
		const char methodNames[eACTIONMETHOD_MAX][cACTIONMETHOD_NAME_MAX] = {
			"mkb/astrology/dailySign001.html",
			"mkb/astrology/timingFortune001.html",
			"mkb/astrology/timingFortune002.html",
			"mkb/astrology/timingFortune003.html",
			"mkb/astrology/timingFortune004.html",
			"mkb/astrology/timingFortune005.html",
			"mkb/astrology/timingFortune006.html",
			"mkb/astrology/timingFortune012.html",
			"mkb/astrology/planetSign001.html",
			"mkb/astrology/planetSign002.html",
			"mkb/astrology/planetSign003.html",
		};

		for (int i = 0; i < eACTIONMETHOD_MAX; i++) {
			if (strcmp(methodNames[i], name) == 0) {
				return i;
			}
		}
		return eACTIONMETHOD_MAX;
	}

	bool createMethodFromRequest(const char* str) {
		this->deleteMethod();

		m_request = new requestFormatter();
		m_request->parse(str, (int)strlen(str) + 1);

		char logicName[0xff];
		if (m_request->getLogicName(logicName) == false) {
			return false;
		}

		int methodId = actionMethod::getMethodId(logicName);

		switch (methodId) {
			case eACTIONMETHOD_DAILYSIGN001:
				m_action = new dailySign001();
				break;

			case eACTIONMETHOD_TIMINGFORTUNE001:
				m_action = new timingFortune001();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE002:
				m_action = new timingFortune002();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE003:
				m_action = new timingFortune003();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE004:
				m_action = new timingFortune004();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE005:
				m_action = new timingFortune005();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE006:
				m_action = new timingFortune006();
				break;
			case eACTIONMETHOD_TIMINGFORTUNE012:
				m_action = new timingFortune012();
				break;

			case eACTIONMETHOD_PLANETSIGN001:
				m_action = new planetSign001();
				break;
			case eACTIONMETHOD_PLANETSIGN002:
				m_action = new planetSign002();
				break;
			case eACTIONMETHOD_PLANETSIGN003:
				m_action = new planetSign003();
				break;
			default:
				return false;
		}
		return true;
	}

	void setFormatType(char formatType) {
		if (m_action != NULL) {
			m_action->createFormatterTop(formatType);
		}
	}

	void parseRequest() {
		m_action->ParseRequest(m_request);
	}
	void Run() {
		m_action->Run(m_request);
	}
	void Print() {
		char buff[0xffff];
		m_action->Print(buff, sizeof(buff));
		printf("%s\n", buff);
	}
	void setSimpleSwitch(bool Switch) {
		m_action->setSimpleSwitch(Switch);
	}

	void deleteMethod(void) {
		if (m_action != NULL) {
			delete m_action;
		}
		if (m_request != NULL) {
			delete m_request;
		}
		m_action = NULL;
		m_request = NULL;
	}
};

#endif
