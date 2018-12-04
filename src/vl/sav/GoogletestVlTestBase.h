/*
 * GoogletestVlTestBase.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLTESTBASE_H_
#define PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLTESTBASE_H_
#include "verilated.h"
#include "verilated_lxt2_c.h"
#include <vector>
#include <stdint.h>
#include <map>

#include "../IEngine.h"

class GoogletestVlTestBase : public IGoogletestHdlBackend {
public:
	GoogletestVlTestBase();

	virtual ~GoogletestVlTestBase();

	virtual void SetUp();

	virtual void TearDown();

	void addClock(CData *clk, double period);

	void addClock(CData &clk, double period);

	virtual void run(double time_ns=-1);

	virtual void raiseObjection(void *obj);

	virtual void dropObjection(void *obj);

protected:

	virtual void eval() const = 0;


protected:
	VerilatedModule									*m_top;
	VerilatedLxt2C 									*m_tfp;
	bool											m_init;
	std::vector<std::pair<CData *, double>>			m_clocks;
	std::vector<ClockStep>							m_steplist;
	uint32_t										m_steplist_idx;
	uint32_t										m_steplist_sz;
	double											m_timestamp;
	std::map<void *, uint32_t>						m_objections;
};

#endif /* PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLTESTBASE_H_ */
