/*
 * GoogletestHdlVl.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: ballance
 */
#include "GoogletestHdl.h"
#include "verilated.h"

/********************************************************************
 * getContext()
 ********************************************************************/
void *GoogletestHdl::getContext() {
	return (void *)Verilated::dpiScope();
}

/********************************************************************
 * setContext()
 ********************************************************************/
void GoogletestHdl::setContext(void *ctxt) {
	return Verilated::dpiScope(reinterpret_cast<const VerilatedScope *>(ctxt));
}

