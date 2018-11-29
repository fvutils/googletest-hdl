/*
 * GoogletestHdlTest.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_TEST_H
#define INCLUDED_GOOGLETEST_HDL_TEST_H
#include <stdint.h>
#include "GoogletestHdlTestBase.h"
#include "IGoogletestHdlTestBase.h"

class GoogletestHdlTest : public GoogletestHdlTestBase {
public:
	typedef GoogletestHdlTestBase BaseT;

	GoogletestHdlTest();

	virtual ~GoogletestHdlTest();

	virtual std::string testname() const;

};

#endif /* INCLUDED_GOOGLETEST_HDL_TEST_H */
