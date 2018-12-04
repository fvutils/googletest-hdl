/*
 * GoogletestHdl.h
 *
 *  Created on: Nov 30, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_H
#define INCLUDED_GOOGLETEST_HDL_H
#include <stdint.h>
#include "gtest/gtest.h"
#include "CmdlineProcessor.h"
#include "IEngine.h"


using namespace gtest_hdl;
class GoogletestHdl : public ::testing::EmptyTestEventListener {
	friend class GoogletestHdlTestListener;
public:
	GoogletestHdl();

	virtual ~GoogletestHdl();

	static GoogletestHdl &inst();

	static const CmdlineProcessor &clp();

	/**
	 * init()
	 *
	 * The initialization function is called back the
	 * launcher to initialize the GoogletestHdl user
	 * layer
	 */
	static void init(
			int 		argc,
			char 		**argv,
			IEngine		*engine);

	static std::string testname();

	// Listener API
	virtual void OnTestStart(const ::testing::TestInfo &test_info);

    virtual void OnTestPartResult(const ::testing::TestPartResult &result);

    virtual void OnTestEnd(const ::testing::TestInfo &test_info);


//	static void SetUp();

	static void raiseObjection();

	static void run();

	static void dropObjection();

//	static void TearDown();

    uint32_t num_tests() const { return m_num_tests; }

    uint32_t num_passed() const { return (m_num_tests - m_num_failed); }

    uint32_t num_failed() const { return m_num_failed; }


protected:
	void OnTestStart();

	void OnTestEnd();

private:
	CmdlineProcessor				m_clp;
	IEngine							*m_engine;
    uint32_t						m_num_tests;
    uint32_t						m_num_failed;

	static GoogletestHdl			m_inst;
};

#endif /* INCLUDED_GOOGLETEST_HDL_H */
