/*
 * GoogletestVlEngineBase.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#include "GoogletestVlEngineBase.h"

GoogletestVlEngineBase::GoogletestVlEngineBase() {
	m_timestamp = 0;
	m_init = false;
	m_objections = 0;
	m_tfp = 0; // TODO:
}

GoogletestVlEngineBase::~GoogletestVlEngineBase() {
	// TODO Auto-generated destructor stub
}

void GoogletestVlEngineBase::addClock(CData &clk, double period) {
	m_clocks.push_back(std::pair<CData *, double>(&clk, period));
}

void GoogletestVlEngineBase::run() {
	fprintf(stdout, "GoogletestVlTestBase::run\n");
	fflush(stdout);
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

//		if (m_timestamp >= time_ns >=0) {
//			remaining -= s.time_incr;
//
//			if (remaining <= 0) {
//				break;
//			}
//		}

		m_steplist_idx = ((m_steplist_idx + 1) % m_steplist_sz);

		if (m_objections == 0) {
			fprintf(stdout, "No objections\n");
			break;
		}
	}
}

void GoogletestVlEngineBase::raiseObjection() {
	m_objections++;
}

void GoogletestVlEngineBase::dropObjection() {
	m_objections--;
}

double GoogletestVlEngineBase::simtime() {
	return m_timestamp;
}

uint32_t									GoogletestVlEngineBase::m_engine_base;

