/*
 * GoogletestHdlTestListener.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#include <stdio.h>
#include "GoogletestHdlTestListener.h"

GoogletestHdlTestListener::GoogletestHdlTestListener() {
	m_num_tests = 0;
	m_num_failed = 0;
}

GoogletestHdlTestListener::~GoogletestHdlTestListener() {
	// TODO Auto-generated destructor stub
}

void GoogletestHdlTestListener::OnTestStart(const ::testing::TestInfo &test_info) {
	// NOP
	fprintf(stdout, "OnTestStart\n");
	m_num_tests++;
}

void GoogletestHdlTestListener::OnTestPartResult(const ::testing::TestPartResult &result) {
	fprintf(stdout, "OnTestPartResult\n");
	if (result.failed()) {
		m_num_failed++;
	}
}

void GoogletestHdlTestListener::OnTestEnd(const ::testing::TestInfo &test_info) {
	// NOP
	fprintf(stdout, "OnTestEnd\n");
}

GoogletestHdlTestListener *GoogletestHdlTestListener::inst() {
	if (!m_inst) {
		m_inst = new GoogletestHdlTestListener();
	}
	return m_inst;
}


GoogletestHdlTestListener *GoogletestHdlTestListener::m_inst = 0;
