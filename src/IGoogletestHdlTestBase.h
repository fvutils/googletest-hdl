/*
 * IGoogletestHdlTestBase.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_IGOOGLETEST_HDL_TEST_BASE_H
#define INCLUDED_IGOOGLETEST_HDL_TEST_BASE_H

class IGoogletestHdlTestBase {
public:

	virtual ~IGoogletestHdlTestBase() { }

	virtual void run(double time_ns=-1) = 0;

	virtual void raiseObjection(void *obj) = 0;

	virtual void dropObjection(void *obj) = 0;

	virtual std::string testname() const = 0;

};




#endif /* INCLUDED_IGOOGLETEST_HDL_TEST_BASE_H */
