/*
 * GoogletestVlTestBase.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#include "GoogletestVlTestBase.h"

GoogletestVlTestBase::GoogletestVlTestBase() {
	m_top = 0;
	m_tfp = 0;
	m_init = false;
	m_timestamp = 0;
	m_steplist_idx = 0;
	m_steplist_sz = 0;
}

GoogletestVlTestBase::~GoogletestVlTestBase() {
	// TODO Auto-generated destructor stub
}

void GoogletestVlTestBase::SetUp() {
	m_clocks.clear();
	m_timestamp = 0;
	m_init = false;

	::testing::UnitTest *test = ::testing::UnitTest::GetInstance();
	fprintf(stdout, "testcases to run: %d\n", test->test_to_run_count());
	fprintf(stdout, " current testcase: %s::%s\n",
			test->current_test_case()->name(),
			test->current_test_info()->name());
}

void GoogletestVlTestBase::run(double time_ns) {
	double remaining = time_ns;
	if (!m_init) {
		m_steplist.push_back(ClockStep(
				m_clocks.at(0).first, 1, m_clocks.at(0).second/2));
		m_steplist.push_back(ClockStep(
				m_clocks.at(0).first, 0, m_clocks.at(0).second/2));
		m_steplist_idx = 0;
		m_steplist_sz = m_steplist.size();
		m_init = true;
	}

	while (true) {
		const ClockStep &s = m_steplist.at(m_steplist_idx);
		*s.clock = s.clock_val;
		eval();
		if (m_tfp) {
			m_tfp->dump(m_timestamp);
		}

		m_timestamp += s.time_incr;

		if (time_ns >=0) {
			remaining -= s.time_incr;

			if (remaining <= 0) {
				break;
			}
		}

		m_steplist_idx = ((m_steplist_idx + 1) % m_steplist_sz);

		if (m_objections.size() == 0) {
			fprintf(stdout, "No objections\n");
			break;
		}
	}

}

void GoogletestVlTestBase::TearDown() {
	delete m_top;
	m_top = 0;

	if (m_tfp) {
		m_tfp->close();
		m_tfp = 0;
	}
}

void GoogletestVlTestBase::addClock(CData *clk, double period) {
	m_clocks.push_back(std::pair<CData *, uint64_t>(clk, period));
}

void GoogletestVlTestBase::addClock(CData &clk, double period) {
	m_clocks.push_back(std::pair<CData *, uint64_t>(&clk, period));
}

std::string GoogletestVlTestBase::testname() const {
	::testing::UnitTest *test = ::testing::UnitTest::GetInstance();
	std::string ret = test->current_test_case()->name();

	ret += ".";
	ret += test->current_test_info()->name();

	return ret;
}

void GoogletestVlTestBase::raiseObjection(void *obj) {
	std::map<void *, uint32_t>::iterator it;

	if ((it=m_objections.find(obj)) == m_objections.end()) {
		m_objections[obj] = 1;
	} else {
		it->second++;
	}
}

void GoogletestVlTestBase::dropObjection(void *obj) {
	std::map<void *, uint32_t>::iterator it;

	if ((it=m_objections.find(obj)) != m_objections.end()) {
		if (it->second <= 1) {
			// Remove
			m_objections.erase(it);
		} else {
			it->second--;
		}
	}
}

