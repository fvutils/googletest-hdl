/*
 * GoogletestVlEngineBase.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#include "GoogletestVlEngineBase.h"
#include "GvmTimeoutException.h"
#include <stdio.h>

#undef DEBUG_EN

#ifdef DEBUG_EN
#define debug(...) fprintf(stdout, __VA_ARGS__) ; fflush(stdout)
#else
#define debug(...)
#endif

GoogletestVlEngineBase::GoogletestVlEngineBase() : m_main_thread(this) {
	m_timestamp = 0;
	m_timeout = 10000; // 1000ns
	m_init = false;
	m_objections = 0;
	m_tfp = 0;
	m_active_thread = &m_main_thread;

	m_runnable_threads.push_back(m_active_thread);
}

GoogletestVlEngineBase::~GoogletestVlEngineBase() {
	// TODO Auto-generated destructor stub
}

void GoogletestVlEngineBase::addClock(CData &clk, double period) {
	m_clocks.push_back(std::pair<CData *, double>(&clk, period));
}

void GoogletestVlEngineBase::init(const ICmdlineProcessor &clp) {
	eval();
}

void GoogletestVlEngineBase::run() {
	debug("GoogletestVlTestBase::run\n");


	while (true) {
		cycle();

		if (m_objections == 0) {
			debug("No objections\n");
			break;
		}
	}
}

void GoogletestVlEngineBase::init() {
	if (!m_init) {
		m_steplist.push_back(ClockStep(
				m_clocks.at(0).first, 1, m_clocks.at(0).second/2));
		m_steplist.push_back(ClockStep(
				m_clocks.at(0).first, 0, m_clocks.at(0).second/2));
		m_steplist_idx = 0;
		m_steplist_sz = m_steplist.size();
		m_init = true;
	}
}

void GoogletestVlEngineBase::cycle() {
	if (!m_init) {
		init();
	}

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

	if (m_timestamp >= m_timeout) {
		throw GvmTimeoutException("Exceeded timeout");
	}

	m_steplist_idx = ((m_steplist_idx + 1) % m_steplist_sz);
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

void GoogletestVlEngineBase::close() {
	if (m_tfp) {
		m_tfp->close();
	}
}

/**
 * Return the current context (ie DPI scope)
 */
void *GoogletestVlEngineBase::getContext() {
	return (void *)Verilated::dpiScope();
}

/**
 * Set the active context (ie DPI scope)
 */
void GoogletestVlEngineBase::setContext(void *ctxt) {
	return Verilated::dpiScope(reinterpret_cast<const VerilatedScope *>(ctxt));
}

	// Create a new thread
GvmThread *GoogletestVlEngineBase::createThread() {
	return 0;
}

// Return the currently-active thread
GvmThread *GoogletestVlEngineBase::activeThread() {
	return m_active_thread;
}

// Block the specified thread
void GoogletestVlEngineBase::blockThread(GvmThread *t) {
	debug("--> blockThread\n");
	// Remove this thread from the runnable list
	for (std::vector<GvmVlThread *>::iterator it=m_runnable_threads.begin();
			it!=m_runnable_threads.end(); it++) {
		if (*it == t) {
			m_runnable_threads.erase(it);
			break;
		}
	}

	// Add this thread to the suspended list
	m_blocked_threads.push_back(static_cast<GvmVlThread *>(t));

	// Swap to a new thread if there is one
	if (t == m_active_thread) {
		// We need to block *this* thread
		while (m_runnable_threads.size() == 0) {
			debug("--> cycle\n");
			cycle();
			debug("<-- cycle\n");
		}
	}
	// Otherwise, just return
	debug("<-- blockThread\n");
}

// Unblock the specified thread
void GoogletestVlEngineBase::unblockThread(GvmThread *t) {
	debug("--> unblockThread\n");
	// Remove this thread from the suspended list
	for (std::vector<GvmVlThread *>::iterator it=m_blocked_threads.begin();
			it!=m_blocked_threads.end(); it++) {
		if (*it == t) {
			m_blocked_threads.erase(it);
			break;
		}
	}

	// Add this thread to the runnable list
	m_runnable_threads.push_back(static_cast<GvmVlThread *>(t));

	// Anything else?
	debug("<-- unblockThread\n");
}

// Yield the active thread
void GoogletestVlEngineBase::yieldThread() {

}

uint32_t									GoogletestVlEngineBase::m_engine_base;

