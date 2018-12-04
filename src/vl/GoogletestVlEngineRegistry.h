/*
 * GoogletestVlEngineRegistry.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEREGISTRY_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEREGISTRY_H_
#include <vector>
#include <map>
#include "GoogletestVlEngineFactoryBase.h"

using namespace gtest_hdl;

class GoogletestVlEngineRegistry {
public:
	GoogletestVlEngineRegistry();

	virtual ~GoogletestVlEngineRegistry();

	static GoogletestVlEngineRegistry &inst() { return m_inst; }

	void add(GoogletestVlEngineFactoryBase *f);

	GoogletestVlEngineFactoryBase *get_default() const;

private:
	static GoogletestVlEngineRegistry				m_inst;

	std::vector<GoogletestVlEngineFactoryBase *>	m_eng_factory_list;


};

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEREGISTRY_H_ */
