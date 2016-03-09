// 2014-12-16 y_ohta

#ifndef _FORMATTERBASE_HPP_
#define _FORMATTERBASE_HPP_

#define cFORMATTER_NAMEBUFF_MAX			(64)
#define cFORMATTER_CHILD_MAX			(256)

class formatterBase {
protected:
	int					m_nest;
	
	char				m_name[cFORMATTER_NAMEBUFF_MAX];
	char*				m_data;
	
	int					m_child_count;
	formatterBase*		m_children[cFORMATTER_CHILD_MAX];

public:
	formatterBase() {
		m_nest = 0;
		m_data = NULL;
		
		m_child_count = 0;
	}
	virtual ~formatterBase() {
		if (m_data != NULL) {
			free(m_data);
			m_data = NULL;
		}
		this->deleteChildren();
	}

protected:
	void deleteChildren() {
		for (int i = 0; i < m_child_count; i++) {
			m_children[i]->deleteChildren();
			delete m_children[i];
			m_children[i] = NULL;
		}
		m_child_count = 0;
	}

public:
	void printTabs(char* buff) {
		for (int i = 0; i < m_nest; i++) {
			strcat(buff, "\t");
		}
	}

	void setNest(int nest) {
		m_nest = nest;
	}
	int getNest(void) {
		return m_nest;
	}

	void setData(const char* data, int dataLength){
		m_data = (char*)malloc(dataLength);
		memcpy(m_data, data, dataLength);
	}

	void setName(const char* name){
		strcpy(m_name, name);
	}

	virtual formatterBase* addChild(const char* name, const char* data, int dataLength) = 0;
	virtual void Print(char* buff, int length) = 0;
};

#endif
