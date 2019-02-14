/*
 * GvmVlThread.h
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */
#pragma once
#include "GvmThread.h"

class GoogletestVlEngineBase;
class GvmVlThread : public GvmThread {
public:
	GvmVlThread(GoogletestVlEngineBase *engine);

	virtual ~GvmVlThread();

protected:

	/** Take this thread off the runnable list */
	virtual void block();

	/** Add this thread back to the runnable list */
	virtual void unblock();

private:
	GoogletestVlEngineBase				*m_engine;
};

