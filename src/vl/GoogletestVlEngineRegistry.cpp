/*
 * GoogletestVlEngineRegistry.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#include "GoogletestVlEngineRegistry.h"

GoogletestVlEngineRegistry::GoogletestVlEngineRegistry() {
	// TODO Auto-generated constructor stub

}

GoogletestVlEngineRegistry::~GoogletestVlEngineRegistry() {
	// TODO Auto-generated destructor stub
}

GoogletestVlEngineFactoryBase *GoogletestVlEngineRegistry::get_default() const {
	if (m_eng_factory_list.size() > 0) {
		return m_eng_factory_list.at(0);
	} else {
		return 0;
	}
}

void GoogletestVlEngineRegistry::add(GoogletestVlEngineFactoryBase *f) {
	m_eng_factory_list.push_back(f);
}

GoogletestVlEngineRegistry GoogletestVlEngineRegistry::m_inst;
