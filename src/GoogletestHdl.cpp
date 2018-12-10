/*
 * GoogletestHdl.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: ballance
 */

#include "GoogletestHdl.h"
#include "gtest/gtest.h"
#include <stdio.h>

class GoogletestHdlTestListener : public ::testing::EmptyTestEventListener {
public:
	GoogletestHdlTestListener(GoogletestHdl *inst) {
		m_inst = inst;
	}

	virtual void OnTestStart(const ::testing::TestInfo &test_info) { m_inst->OnTestStart(test_info); }

    virtual void OnTestPartResult(const ::testing::TestPartResult &result) { m_inst->OnTestPartResult(result); }

    virtual void OnTestEnd(const ::testing::TestInfo &test_info) { m_inst->OnTestEnd(test_info); }


private:
	GoogletestHdl				*m_inst;
};

GoogletestHdl::GoogletestHdl() {
	fprintf(stdout, "GoogletestHdl::GoogletestHdl\n");
	fflush(stdout);
	// TODO Auto-generated constructor stub

}

GoogletestHdl::~GoogletestHdl() {
	// TODO Auto-generated destructor stub
}

GoogletestHdl &GoogletestHdl::inst() {
	return m_inst;
}

void GoogletestHdl::init(int argc, char **argv, IEngine *engine) {
	m_inst.m_clp.init(argc, argv);
	m_inst.m_engine = engine;

	if (m_inst.m_engine) {
		fprintf(stdout, "INIT\n");
		fflush(stdout);
		m_inst.m_engine->init(m_inst.m_clp);
	}

	GoogletestHdlTestListener *l = new GoogletestHdlTestListener(&m_inst);
	// Register ourselves as a listener
	::testing::TestEventListeners &listeners =
			::testing::UnitTest::GetInstance()->listeners();
	listeners.Append(l);
}

const CmdlineProcessor &GoogletestHdl::clp() {
	return m_inst.m_clp;
}

std::string GoogletestHdl::testname() {
	::testing::UnitTest *test = ::testing::UnitTest::GetInstance();
	std::string ret = test->current_test_case()->name();

	ret += ".";
	ret += test->current_test_info()->name();

	return ret;
}

void GoogletestHdl::OnTestStart(const ::testing::TestInfo &test_info) {
	m_num_tests++;
}

void GoogletestHdl::OnTestPartResult(const ::testing::TestPartResult &result) {
	if (result.failed()) {
		m_num_failed++;
	}

}

void GoogletestHdl::OnTestEnd(const ::testing::TestInfo &test_info) {

}

void GoogletestHdl::raiseObjection() {
	inst().m_engine->raiseObjection();
}

void GoogletestHdl::run() {
	fprintf(stdout, "-- run: m_engine=%p\n", inst().m_engine);
	inst().m_engine->run();
}

void GoogletestHdl::dropObjection() {
	fprintf(stdout, "--> m_engine=%p\n", inst().m_engine);
	fflush(stdout);
	inst().m_engine->dropObjection();
	fprintf(stdout, "<-- m_engine=%p\n", inst().m_engine);
	fflush(stdout);
}

GoogletestHdl GoogletestHdl::m_inst;

