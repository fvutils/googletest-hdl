/*
 * GoogletestVlTestBaseT.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_VL_TEST_H
#define INCLUDED_GOOGLETEST_VL_TEST_H
#include <stdint.h>
#include "gtest/gtest.h"
#include "verilated.h"
#include "verilated_lxt2_c.h"
#include <vector>
#include <stdint.h>
#include <map>
#include "../IGoogletestHdlBackend.h"

template <class T> class GoogletestVlTestBaseT : public IGoogletestHdlBackend {
public:
	typedef GoogletestVlTestBaseT<T> BaseT;
public:
	GoogletestVlTestBaseT();

	virtual ~GoogletestVlTestBaseT();

	void addClock(CData &clk, double period);

	virtual void run(double time_ns=-1);

	virtual void raiseObjection(void *obj);

	virtual void dropObjection(void *obj);

protected:
	T							*m_top;

private:

	struct ClockStep {
		CData			*clock;
		uint8_t			clock_val;
		double			time_incr;

		ClockStep(CData *clock, uint8_t clock_val, double time_incr) {
			this->clock     = clock;
			this->clock_val = clock_val;
			this->time_incr = time_incr;
		}
	};

private:
	VerilatedLxt2C 									*m_tfp;
	bool											m_init;
	std::vector<std::pair<CData *, double>>			m_clocks;
	std::vector<ClockStep>							m_steplist;
	uint32_t										m_steplist_idx;
	uint32_t										m_steplist_sz;
	double											m_timestamp;
	std::map<void *, uint32_t>						m_objections;

};

template <class T> GoogletestVlTestBaseT<T>::GoogletestVlTestBaseT() {
	m_init = false;
	m_steplist_idx = 0;
	m_steplist_sz = 0;
	m_timestamp = 0;

	m_top = new T();

	m_tfp = new VerilatedLxt2C();
	m_top->trace(m_tfp, 99);

	m_tfp->open("simx.lxt");
}

template <class T> GoogletestVlTestBaseT<T>::~GoogletestVlTestBaseT() {
	delete m_top;

	if (m_tfp) {
		m_tfp->close();
		m_tfp = 0;
	}
}

template <class T> void GoogletestVlTestBaseT<T>::run(double time_ns) {
	double remaining = time_ns;

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
		m_top->eval();
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

template <class T> void GoogletestVlTestBaseT<T>::addClock(CData &clk, double period) {
	m_clocks.push_back(std::pair<CData *, uint64_t>(&clk, period));
}

template <class T> void GoogletestVlTestBaseT<T>::raiseObjection(void *obj) {
	std::map<void *, uint32_t>::iterator it;

	if ((it=m_objections.find(obj)) == m_objections.end()) {
		m_objections[obj] = 1;
	} else {
		it->second++;
	}
}

template <class T> void GoogletestVlTestBaseT<T>::dropObjection(void *obj) {
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

#endif /* INCLUDED_GOOGLETEST_VL_TEST_H */
