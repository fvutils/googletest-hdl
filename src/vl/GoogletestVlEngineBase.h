/*
 * GoogletestVlEngineBase.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */
#pragma once
#include "IEngine.h"
#include "ICmdlineProcessor.h"
#include "GvmVlThread.h"
#include <vector>
#include <stdint.h>
#include "gtest/gtest.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <stdint.h>
#include <map>

using namespace gtest_hdl;

class GoogletestVlEngineBase : public virtual gtest_hdl::IEngine {
public:
	GoogletestVlEngineBase();

	virtual ~GoogletestVlEngineBase();

	void addClock(CData &clk, double period);

	virtual void init(const ICmdlineProcessor &clp);

	virtual void run();

	virtual void raiseObjection();

	virtual void dropObjection();

	virtual double simtime();

	virtual void close();

	/**
	 * Return the current context (ie DPI scope)
	 */
	virtual void *getContext();

	/**
	 * Set the active context (ie DPI scope)
	 */
	virtual void setContext(void *ctxt);

	// Create a new thread
	virtual GvmThread *createThread();

	// Return the currently-active thread
	virtual GvmThread *activeThread();

	// Block the specified thread
	virtual void blockThread(GvmThread *t);

	// Unblock the specified thread
	virtual void unblockThread(GvmThread *t);

	// Yield the active thread
	virtual void yieldThread();

protected:

	virtual void eval() = 0;

	virtual void trace() = 0;

	void init();

	void cycle();

protected:

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

protected:
	VerilatedFstC 									*m_tfp;
	GvmVlThread										m_main_thread;
	GvmVlThread										*m_active_thread;
	std::vector<GvmVlThread *>						m_runnable_threads;
	std::vector<GvmVlThread *>						m_blocked_threads;
	bool											m_init;
	std::vector<std::pair<CData *, double>>			m_clocks;
	std::vector<ClockStep>							m_steplist;
	uint32_t										m_steplist_idx;
	uint32_t										m_steplist_sz;
	double											m_timestamp;
	double											m_timeout;
	uint32_t										m_objections;

	static uint32_t									m_engine_base;
};


