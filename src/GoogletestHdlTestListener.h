/*
 * GoogletestHdlTestListener.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_TEST_LISTENER_H
#define INCLUDED_GOOGLETEST_HDL_TEST_LISTENER_H
#include <stdint.h>
#include "gtest/gtest.h"

class GoogletestHdlTestListener : public ::testing::EmptyTestEventListener {
public:
	GoogletestHdlTestListener();

	virtual ~GoogletestHdlTestListener();

    virtual void OnTestStart(const ::testing::TestInfo &test_info);

    virtual void OnTestPartResult(const ::testing::TestPartResult &result);

    virtual void OnTestEnd(const ::testing::TestInfo &test_info);

    uint32_t num_tests() const { return m_num_tests; }

    uint32_t num_passed() const { return (m_num_tests - m_num_failed); }

    uint32_t num_failed() const { return m_num_failed; }

    static GoogletestHdlTestListener *inst();


private:
    uint32_t							m_num_tests;
    uint32_t							m_num_failed;

    static GoogletestHdlTestListener	*m_inst;


};

#endif /* INCLUDED_GOOGLETEST_HDL_TEST_LISTENER_H */
