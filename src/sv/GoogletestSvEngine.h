/*
 * GoogletestSvEngine.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#pragma once
#include "gtest/gtest.h"
#include "IEngine.h"
#include "GvmSvThread.h"


namespace gtest_hdl {
class ICmdlineProcessor;
}

class GoogletestSvEngine : public virtual gtest_hdl::IEngine {
public:
	GoogletestSvEngine();

	virtual ~GoogletestSvEngine();

	virtual void init(const gtest_hdl::ICmdlineProcessor &clp);

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

private:
	void					*m_main_ctxt;
	GvmSvThread				m_main_thread;
	GvmSvThread				*m_active_thread;


};

