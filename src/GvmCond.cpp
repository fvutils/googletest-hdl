/*
 * GvmCond.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */

#include "GvmCond.h"
#include "GvmThread.h"
#include "GvmMutex.h"

GvmCond::GvmCond() {
	// TODO Auto-generated constructor stub

}

GvmCond::~GvmCond() {
	// TODO Auto-generated destructor stub
}

void GvmCond::wait(GvmMutex &mutex) {
	GvmThread *active = GvmThread::self();

	m_notify_list.push_back(active);
	// Unlock the mutex before going to sleep
	active->block(mutex);
}

void GvmCond::notify() {
	if (m_notify_list.size() > 0) {
		GvmThread *t = m_notify_list.front();
		m_notify_list.erase(m_notify_list.begin());
		t->unblock();
	}
}

void GvmCond::notify_all() {
	for (std::vector<GvmThread *>::iterator it=m_notify_list.begin();
			it!=m_notify_list.end(); it++) {
		(*it)->unblock();
	}
	m_notify_list.clear();
}

