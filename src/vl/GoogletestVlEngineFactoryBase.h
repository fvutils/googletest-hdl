/*
 * GoogletestVlEngineFactoryBase.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEFACTORYBASE_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEFACTORYBASE_H_
#include <string>
#include <typeinfo>
#include "IEngine.h"

using namespace gtest_hdl;

class GoogletestVlEngineFactoryBase {
public:
	GoogletestVlEngineFactoryBase(const std::type_info &type);

	virtual ~GoogletestVlEngineFactoryBase();

	const std::string &get_typename() const { return m_typename; }

	virtual IEngine *create() const = 0;

private:
	std::string				m_typename;
};

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEFACTORYBASE_H_ */
