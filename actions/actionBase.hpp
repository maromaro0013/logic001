// 2014-12-28 y_ohta

#ifndef _ACTIONBASE_HPP_
#define _ACTIONBASE_HPP_

#include "../formatter/requestFormatter.hpp"
#include "../formatter/xmlFormatter.hpp"
#include "../formatter/jsonFormatter.hpp"

#define cACTIONBASE_ERRMSG_MAX		(64)

class actionBase {
protected:
	formatterBase*		m_top;
	char				m_errmsg[cACTIONBASE_ERRMSG_MAX];

	bool				m_simpleSwitch;

public:
	actionBase() {
		m_top = new xmlFormatter("results");
		memset(m_errmsg, 0, sizeof(m_errmsg));

		m_simpleSwitch = false;
	}

	virtual ~actionBase() {
		if (m_top != NULL) {
			delete m_top;
			m_top = NULL;
		}
	}

protected:
	void setErrmsg(char* buff) {
		if (strlen(buff) < cACTIONBASE_ERRMSG_MAX) {
			strcpy(m_errmsg, buff);
		}
	}

public:
	formatterBase* getFormatterTop() {
		return m_top;
	}
	void createFormatterTop(char formatType) {
		if (m_top != NULL) {
			delete m_top;
			m_top = NULL;
		}
		switch (formatType) {
			case 'x':
				m_top = new xmlFormatter("results");
				break;
			case 'j':
				m_top = new jsonFormatter("results");
				break;

			default:
				m_top = new xmlFormatter("results");
				break;
		}
	}

public:
	void setSimpleSwitch(bool Switch) {
		m_simpleSwitch = Switch;
	}

	virtual bool ParseRequest(requestFormatter* format) = 0;
	virtual bool Run(requestFormatter* request) = 0;

	virtual void Print(char* buff, int length) {
		buff[0] = '\0';
		m_top->Print(buff, length);
	}
	virtual void getErrmsg(char* buff, int length) {
		if (length >= cACTIONBASE_ERRMSG_MAX) {
			strcpy(buff, m_errmsg);
		}
	}
};

#endif