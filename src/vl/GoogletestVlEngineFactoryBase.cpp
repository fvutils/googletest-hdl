/*
 * GoogletestVlEngineFactoryBase.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#include "GoogletestVlEngineFactoryBase.h"
#include "GoogletestVlEngineRegistry.h"
#include <stdio.h>

GoogletestVlEngineFactoryBase::GoogletestVlEngineFactoryBase(const std::type_info &type) {
	fprintf(stdout, "GoogletestVlEngineFactoryBase\n");
	fflush(stdout);
	GoogletestVlEngineRegistry::inst().add(this);
}

GoogletestVlEngineFactoryBase::~GoogletestVlEngineFactoryBase() {
	// TODO Auto-generated destructor stub
}

