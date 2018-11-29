/*
 * GoogletestHdlTestBase.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_TEST_BASE_H
#define INCLUDED_GOOGLETEST_HDL_TEST_BASE_H
#include "gtest/gtest.h"
#include "IGoogletestHdlTestBase.h"

class GoogletestHdlTestBase :
		public ::testing::Test,
		public virtual IGoogletestHdlTestBase {
public:
	GoogletestHdlTestBase();

	virtual ~GoogletestHdlTestBase();

	virtual void run(double time_ns=-1) { }

	virtual void raiseObjection(void *obj) { }

	virtual void dropObjection(void *obj) { }

};

#endif /* INCLUDED_GOOGLETEST_HDL_TEST_BASE_H */
