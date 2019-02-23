/*
 * GvmSvThread.h
 *
 *  Created on: Feb 17, 2019
 *      Author: ballance
 */
#pragma once
#include "GvmThread.h"

class GoogletestSvEngine;
class GvmSvThread : public GvmThread {
public:
	GvmSvThread(GoogletestSvEngine *engine);

	virtual ~GvmSvThread();

protected:

	/** Take this thread off the runnable list */
	virtual void block();

	/** Add this thread back to the runnable list */
	virtual void unblock();

private:
	GoogletestSvEngine				*m_engine;

};

