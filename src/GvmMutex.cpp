/*
 * GvmMutex.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */

#include "GvmMutex.h"
#include "GvmThread.h"

GvmMutex::GvmMutex() : m_owner(0), m_block_list(0) {
	// TODO Auto-generated constructor stub

}

GvmMutex::~GvmMutex() {
	// TODO Auto-generated destructor stub
}

void GvmMutex::lock() {
	GvmThread *active_t = GvmThread::self();

	if (m_owner) {
		// Add ourselves to a wait list and block
		active_t->set_next(m_block_list);
		m_block_list = active_t;
		active_t->block();
		// When we unblock, we should own the mutex
	}
	m_owner = active_t;
}

void GvmMutex::unlock() {
	m_owner = 0;

	if (m_block_list) {
		// Unblock one of the threads
		GvmThread *t = m_block_list;
		m_block_list = t->get_next();
		t->set_next(0); // housekeeping
		t->unblock(); // Move the thread back to the ready list
	}
}
