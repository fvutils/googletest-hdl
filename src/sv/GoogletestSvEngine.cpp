/*
 * GoogletestSvEngine.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#include "googletest_sv.h"
#include "GoogletestSvEngine.h"

GoogletestSvEngine::GoogletestSvEngine() {
	// TODO Auto-generated constructor stub

}

GoogletestSvEngine::~GoogletestSvEngine() {
	// TODO Auto-generated destructor stub
}

void GoogletestSvEngine::run() {
	googletest_sv_run();
}

void GoogletestSvEngine::raiseObjection() {
	googletest_sv_raise_objection();
}

void GoogletestSvEngine::dropObjection() {
	fprintf(stdout, "--> SvEngine::dropObjection\n");
	fflush(stdout);
	googletest_sv_drop_objection();
	fprintf(stdout, "<-- SvEngine::dropObjection\n");
	fflush(stdout);
}

double GoogletestSvEngine::simtime() {
	return 0.0; // TODO:
}
