#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "actions/actionMethod.hpp"

#define cLOGIC_REQUEST_MAX		(32)

int main(int argc, const char * argv[]) {
	
	if (argc <= 1) {
		return 0;
	}
	

	int request_cnt = 0;
	char tmp[1024];
	char params[cLOGIC_REQUEST_MAX][1024];
	bool simpleSwitch = false;
	bool nameMode = false;
	char formatType = 'x';

//	char test[] = "mkb/astrology/timingFortune012.html?bymd1=19961224&bhms1=041135&bpref1=38&ymd=20040324&houseId=9&planetId=2&pattern=0";
//	char test[] = "mkb/astrology/timingFortune012.html?bymd1=19720517&bhms1=203830&bpref1=1&ymd=20140802&houseId=5&planetId=5&pattern=0";

	for (int i = 1; i < argc; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, argv[i]);
		if (tmp[0] == '-') {
			switch (tmp[1]) {
/*
				case 't':
					simpleSwitch = true;
					break;
*/
				case 'n':
					nameMode = true;
					break;
				case 'j':
					formatType = 'j';
					break;
				case 'x':
					formatType = 'x';
					break;
			}
		}
		else {
			strcpy(params[request_cnt], argv[i]);
			request_cnt++;
		}
	}

	if (nameMode == true) {
		int id = actionMethod::getMethodId(params[0]);
		if (id < eACTIONMETHOD_MAX) {
			printf("true\n");
		}
		else {
			printf("false\n");
		}
	}
	else {
		actionMethod* method = new actionMethod();
		bool ret = method->createMethodFromRequest(params[0]);
		if (ret == false) {
			return -1;
		}
		method->setFormatType(formatType);
		method->setSimpleSwitch(simpleSwitch);
		method->parseRequest();
		method->Run();
		method->Print();

		delete method;
	}

	return 0;
}