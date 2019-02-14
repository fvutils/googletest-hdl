/*
 * GvmThread.h
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */
#pragma once

namespace gtest_hdl {
class IEngine;
}

class GvmMutex;
class GvmThread {
public:
	friend class GvmMutex;
	friend class GvmCond;

	virtual ~GvmThread();

	/**
	 * Create a new thread
	 */
	static GvmThread *create();

	/**
	 * Return the active thread
	 */
	static GvmThread *self();

	void set_next(GvmThread *next) { m_next = next; }

	GvmThread *get_next() const { return m_next; }

protected:
	GvmThread();

	// Block this thread, while unlocking/locking the specified mutex
	void block(GvmMutex &mutex);

	/** Take this thread off the runnable list */
	virtual void block() = 0;

	/** Add this thread back to the runnable list */
	virtual void unblock() = 0;

private:

	GvmThread				*m_next;
};

