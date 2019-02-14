/*
 * GvmThread.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */

#include "GvmThread.h"
#include "GvmMutex.h"
#include "IEngine.h"
#include "GoogletestHdl.h"

using namespace gtest_hdl;

GvmThread::GvmThread() {
	// TODO Auto-generated constructor stub

}

GvmThread::~GvmThread() {
	// TODO Auto-generated destructor stub
}

void GvmThread::block(GvmMutex &mutex) {
	mutex.unlock();
	block();
	mutex.lock();
}

GvmThread *GvmThread::self() {
	return GoogletestHdl::activeThread();
}

