/*
 * GoogletestUvmEngine.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_TEST_BASE_H
#define INCLUDED_GOOGLETEST_HDL_TEST_BASE_H
#include "gtest/gtest.h"
#include "IEngine.h"

class GoogletestUvmEngine : public virtual gtest_hdl::IEngine {
public:
	GoogletestUvmEngine();

	virtual ~GoogletestUvmEngine();

	virtual void run();

	virtual void raiseObjection();

	virtual void dropObjection();

	virtual double simtime();

};

#endif /* INCLUDED_GOOGLETEST_HDL_TEST_BASE_H */
