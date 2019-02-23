/*
 * GvmSvThread.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: ballance
 */

#include "GvmSvThread.h"
#include "GoogletestSvEngine.h"

GvmSvThread::GvmSvThread(GoogletestSvEngine *engine) : m_engine(engine) {
	// TODO Auto-generated constructor stub

}

GvmSvThread::~GvmSvThread() {
	// TODO Auto-generated destructor stub
}

	/** Take this thread off the runnable list */
void GvmSvThread::block() {
	m_engine->blockThread(this);
}

	/** Add this thread back to the runnable list */
void GvmSvThread::unblock() {
	m_engine->unblockThread(this);
}
