// 2014-12-03 y_ohta

#ifndef _XMLFORMATTER_HPP_
#define _XMLFORMATTER_HPP_

#include "formatterBase.hpp"

class xmlFormatter : public formatterBase {
public:
	xmlFormatter() {
		;
	}
	xmlFormatter(const char* name) {
		strcpy(m_name, name);
	}
	~xmlFormatter() {
	}

private:
	void printTag(char* buff, const char* tagname, bool end) {
		if (end) {
			strcat(buff, "</");
		}
		else {
			strcat(buff, "<");
		}
		strcat(buff, tagname);
		strcat(buff, ">");
	}

public:
	formatterBase* addChild(const char* name, const char* data, int dataLength) {
		if (m_child_count >= cFORMATTER_CHILD_MAX) {
			return NULL;
		}
		m_children[m_child_count] = new xmlFormatter(name);
		if (dataLength > 0) {
			m_children[m_child_count]->setData(data, dataLength);
		}
		m_children[m_child_count]->setNest(this->getNest() + 1);
		m_child_count++;
		
		return m_children[m_child_count - 1];
	}
	
	void Print(char* buff, int length) {
		if (m_nest == 0) {
			strcat(buff, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
			strcat(buff, "\n");
		}
		
		this->printTabs(buff);
		this->printTag(buff, m_name,false);
		if (m_child_count > 0) {
			for (int i = 0; i < m_child_count; i++) {
				strcat(buff, "\n");
				m_children[i]->Print(buff, length);
			}
			
			strcat(buff, "\n");
			this->printTabs(buff);
		}
		else if (m_data != NULL) {
			strcat(buff, m_data);
		}
		
		this->printTag(buff, m_name, true);
	}
};

#endif//_XMLFORMATTER_HPP_
