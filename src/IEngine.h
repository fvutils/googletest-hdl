/*
 * IEngine.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */
#pragma once

class GvmThread;
namespace gtest_hdl {
class ICmdlineProcessor;

class IEngine {
public:

	virtual ~IEngine() { }

	/**
	 * Initialize the environment, allowing any time-0
	 * registrations to occur
	 */
	virtual void init(const ICmdlineProcessor &clp) = 0;

	virtual void run() = 0;

	virtual void raiseObjection() = 0;

	virtual void dropObjection() = 0;

	virtual double simtime() = 0;

	virtual void close() = 0;

	/**
	 * Return the current context (ie DPI scope)
	 */
	virtual void *getContext() = 0;

	/**
	 * Set the active context (ie DPI scope)
	 */
	virtual void setContext(void *ctxt) = 0;

	// Create a new thread
	virtual GvmThread *createThread() = 0;

	// Return the currently-active thread
	virtual GvmThread *activeThread() = 0;

	// Block the specified thread
	virtual void blockThread(GvmThread *t) = 0;

	// Unblock the specified thread
	virtual void unblockThread(GvmThread *t) = 0;

	// Yield the active thread
	virtual void yieldThread() = 0;

};

}


