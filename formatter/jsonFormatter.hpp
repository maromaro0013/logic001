// 2014-12-16 y_ohta

#ifndef _JSONFORMATTER_HPP_
#define _JSONFORMATTER_HPP_

#include "formatterBase.hpp"

class jsonFormatter : public formatterBase {
public:
	jsonFormatter() {
		;
	}
	jsonFormatter(const char* name) {
		strcpy(m_name, name);
	}
	~jsonFormatter() {
	}

	formatterBase* addChild(const char* name, const char* data, int dataLength) {
		if (m_child_count >= cFORMATTER_CHILD_MAX) {
			return NULL;
		}
		m_children[m_child_count] = new jsonFormatter(name);
		if (dataLength > 0) {
			m_children[m_child_count]->setData(data, dataLength);
		}
		m_children[m_child_count]->setNest(this->getNest() + 1);
		m_child_count++;
		
		return m_children[m_child_count - 1];
	}
	
	void Print(char* buff, int length) {
		if (m_nest == 0) {
			strcat(buff, "{");
			strcat(buff, "\n");
		}
		this->printTabs(buff);

		strcat(buff, "\"");
		strcat(buff, m_name);
		strcat(buff, "\":");

		if (m_child_count > 0) {
			strcat(buff, "{");
			for (int i = 0; i < m_child_count; i++) {
				strcat(buff, "\n");
				m_children[i]->Print(buff, length);
				if (i < (m_child_count - 1)) {
					strcat(buff, ",");
				}
			}
			strcat(buff, "}");
		}
		else if (m_data != NULL) {
			strcat(buff, "\"");
			strcat(buff, m_data);
			strcat(buff, "\"");
		}
		else {
			strcat(buff, "}");
		}
		
		if (m_nest == 0) {
			strcat(buff, "\n");
			strcat(buff, "}");
		}
	}
};

#endif
