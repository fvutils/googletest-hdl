/*
 * GoogletestUvmEngine.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#include "googletest_uvm.h"
#include "GoogletestUvmEngine.h"

GoogletestUvmEngine::GoogletestUvmEngine() {
	// TODO Auto-generated constructor stub

}

GoogletestUvmEngine::~GoogletestUvmEngine() {
	// TODO Auto-generated destructor stub
}

void GoogletestUvmEngine::run() {
	googletest_uvm_run();
}

void GoogletestUvmEngine::raiseObjection() {
	googletest_uvm_raise_objection();
}

void GoogletestUvmEngine::dropObjection() {
	googletest_uvm_drop_objection();
}

double GoogletestUvmEngine::simtime() {
	return 0.0; // TODO:
}
