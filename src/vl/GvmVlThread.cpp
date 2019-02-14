/*
 * GvmVlThread.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */

#include "GvmVlThread.h"
#include "GoogletestVlEngineBase.h"
#include <stdio.h>

GvmVlThread::GvmVlThread(GoogletestVlEngineBase *engine) : m_engine(engine) {
	// TODO Auto-generated constructor stub

}

GvmVlThread::~GvmVlThread() {
	// TODO Auto-generated destructor stub
}

/** Take this thread off the runnable list */
void GvmVlThread::block() {
	m_engine->blockThread(this);
}

/** Add this thread back to the runnable list */
void GvmVlThread::unblock() {
	m_engine->unblockThread(this);
}

