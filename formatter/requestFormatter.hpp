// 2014-01-03 y_ohta

#ifndef _REQUESTFORMATTER_HPP_
#define _REQUESTFORMATTER_HPP_

#define cREQUEST_PARAMCOUNT_MAX		(64)
#define cREQUEST_PARAMNAME_MAX		(64)
#define cREQUEST_PARAMSTR_MAX		(64)
#define cREQUEST_LOGICNAME_MAX		(256)
#define cREQUEST_PARAM_ERROR		(INT_MAX)

#include "../core/Date.hpp"

class requestFormatter {
private:
	char*				m_request;
	Date*				m_Ymd;
	Date*				m_bymd1;
	Date*				m_bymd2;

	int					m_paramcount;
	char				m_logicName[cREQUEST_LOGICNAME_MAX];
	char				m_paramNames[cREQUEST_PARAMCOUNT_MAX][cREQUEST_PARAMNAME_MAX];
	char				m_params[cREQUEST_PARAMCOUNT_MAX][cREQUEST_PARAMSTR_MAX];

public:
	requestFormatter(void) {
		m_request = NULL;

		m_Ymd = new Date();
		m_bymd1 = new Date();
		m_bymd2 = new Date();
	}
	~requestFormatter() {
		if (m_request != NULL) {
			free(m_request);
			m_request = NULL;
		}
		if (m_Ymd != NULL) {
			delete m_Ymd;
		}
		if (m_bymd1 != NULL) {
			delete m_bymd1;
		}
		if (m_bymd2 != NULL) {
			delete m_bymd2;
		}
	}

private:
	bool perseDate(void) {
		char buff[cREQUEST_PARAMSTR_MAX];

		for (int i = 0; i < m_paramcount; i++) {
			strcpy(buff, m_params[i]);
			if (strcmp(m_paramNames[i], "bymd1") == 0) {
				if (strlen(buff) != 8) {
					return false;
				}
				char y[16];
				char m[16];
				char d[16];
				strcpy(y, buff);
				y[4] = '\0';
				strcpy(m, &buff[4]);
				m[2] = '\0';
				strcpy(d, &buff[6]);
				m_bymd1->setDate(atoi(y), atoi(m), atoi(d));
			}
			else if (strcmp(m_paramNames[i], "bhms1") == 0) {
				if (strlen(buff) != 6) {
					return false;
				}
				char h[16];
				char m[16];
				char s[16];
				strcpy(h, buff);
				h[2] = '\0';
				strcpy(m, &buff[2]);
				m[2] = '\0';
				strcpy(s, &buff[4]);
				m_bymd1->setTime(atoi(h), atoi(m), atoi(s));
			}
			else if (strcmp(m_paramNames[i], "bymd2") == 0) {
				if (strlen(buff) != 8) {
					return false;
				}
				char y[16];
				char m[16];
				char d[16];
				strcpy(y, buff);
				y[4] = '\0';
				strcpy(m, &buff[4]);
				m[2] = '\0';
				strcpy(d, &buff[6]);
				m_bymd2->setDate(atoi(y), atoi(m), atoi(d));
			}
			else if (strcmp(m_paramNames[i], "bhms2") == 0) {
				if (strlen(buff) != 6) {
					return false;
				}
				char h[16];
				char m[16];
				char s[16];
				strcpy(h, buff);
				h[2] = '\0';
				strcpy(m, &buff[2]);
				m[2] = '\0';
				strcpy(s, &buff[4]);
				m_bymd2->setTime(atoi(h), atoi(m), atoi(s));
			}
			else if (strcmp(m_paramNames[i], "ymd") == 0) {
				if (strlen(buff) != 8) {
					return false;
				}
				char y[16];
				char m[16];
				char d[16];
				strcpy(y, buff);
				y[4] = '\0';
				strcpy(m, &buff[4]);
				m[2] = '\0';
				strcpy(d, &buff[6]);
				m_Ymd->setDate(atoi(y), atoi(m), atoi(d));
			}
		}

		return true;
	}

public:
	bool parse(const char* params, int buffLength) {
		int pos = 0;
		int tmp = 0;

		// get logic name
		for (tmp = pos; tmp < buffLength; tmp++) {
			if (params[tmp] == '?') {
				break;
			}
		}
		if (tmp >= buffLength) {
			return false;
		}
		if ((tmp - pos) < cREQUEST_LOGICNAME_MAX) {
			strcpy(m_logicName, &params[pos]);
			m_logicName[(tmp - pos)] = '\0';
		}
		pos = tmp + 1;

		// get params
		m_paramcount = 0;
		for (tmp = pos; tmp < buffLength; tmp++) {
			if (params[tmp] == '&' || params[tmp] == '\0') {
				char tmpstr[0xffff];
				strcpy(tmpstr, &params[pos]);
				tmpstr[(tmp - pos)] = '\0';

				for (int i = 0; i < (int)strlen(tmpstr); i++) {
					if (tmpstr[i] == '=' && (i + 1) < (int)strlen(tmpstr)) {
						char name[0xffff];
						char param[0xffff];
						strcpy(name, tmpstr);
						name[i] = '\0';
						strcpy(param, &tmpstr[i + 1]);

						strcpy(m_paramNames[m_paramcount], name);
						strcpy(m_params[m_paramcount], param);
						m_paramcount++;
						break;
					}
				}
				pos = tmp + 1;
			}
		}

		// date paramas
		this->perseDate();

		return true;
	}

	int getIntParam(const char* paramname) {
		for (int i = 0; i < m_paramcount; i++) {
			if (strcmp(paramname, m_paramNames[i]) == 0) {
				return atoi(m_params[i]);
			}
		}
		return cREQUEST_PARAM_ERROR;
	}
	int getStringParam(const char* paramname, char* dest) {
		for (int i = 0; i < m_paramcount; i++) {
			if (strcmp(paramname, m_paramNames[i]) == 0) {
				strcpy(dest, m_params[i]);
				return 1;
			}
		}
		return cREQUEST_PARAM_ERROR;
	}

	bool getLogicName(char* dest) {
		if (m_logicName[0] != NULL) {
			strcpy(dest, m_logicName);
			return true;
		}
		return false;
	}

	Date* const getYmd(void) {
		return m_Ymd;
	}
	Date* const getBymd1(void) {
		return m_bymd1;
	}
	Date* const getBymd2(void) {
		return m_bymd2;
	}

	void printParams(void) {
		for (int i = 0; i < m_paramcount; i++) {
			printf("%s:%s\n", m_paramNames[i], m_params[i]);
		}
	}
};

#endif//_REQUESTFORMATTER_HPP_
