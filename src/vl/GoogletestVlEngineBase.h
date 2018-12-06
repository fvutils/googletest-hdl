/*
 * GoogletestVlEngineBase.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEBASE_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEBASE_H_
#include "IEngine.h"
#include <vector>
#include <stdint.h>
#include "gtest/gtest.h"
#include "verilated.h"
#include "verilated_lxt2_c.h"
#include <stdint.h>
#include <map>

class GoogletestVlEngineBase : public virtual gtest_hdl::IEngine {
public:
	GoogletestVlEngineBase();

	virtual ~GoogletestVlEngineBase();

	void addClock(CData &clk, double period);

	virtual void init();

	virtual void run();

	virtual void raiseObjection();

	virtual void dropObjection();

	virtual double simtime();

protected:

	virtual void eval() = 0;

	virtual void trace() = 0;

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
	uint32_t										m_objections;

	static uint32_t									m_engine_base;
};

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINEBASE_H_ */
