/*
 * GoogletestHdlTest.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#include "GoogletestHdlTest.h"

GoogletestHdlTest::GoogletestHdlTest() {
	// TODO Auto-generated constructor stub

}

GoogletestHdlTest::~GoogletestHdlTest() {
	// TODO Auto-generated destructor stub
}

std::string GoogletestHdlTest::testname() const {
	::testing::UnitTest *test = ::testing::UnitTest::GetInstance();
	std::string ret = test->current_test_case()->name();

	ret += ".";
	ret += test->current_test_info()->name();

	return ret;
}
