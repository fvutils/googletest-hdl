/*
 * GoogletestHdlVl.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: ballance
 */
#include "GoogletestHdl.h"

extern "C" {
void *svGetScope();
void svSetScope(void *);
}

/********************************************************************
 * getContext()
 ********************************************************************/
void *GoogletestHdl::getContext() {
	return svGetScope();
}

/********************************************************************
 * setContext()
 ********************************************************************/
void GoogletestHdl::setContext(void *ctxt) {
	svSetScope(ctxt);
}

