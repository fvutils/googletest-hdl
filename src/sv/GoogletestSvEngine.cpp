/*
 * GoogletestSvEngine.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#include "googletest_sv.h"
#include "GoogletestSvEngine.h"
#include <stdio.h>

extern "C" {
void *svGetScope();
void svSetScope(void *);
int _blockThread(void *thread);
int _unblockThread(void *thread);
int _yieldThread();
void _registerThread(void *thread);
}

GoogletestSvEngine::GoogletestSvEngine() : m_main_thread(this) {
	m_active_thread = &m_main_thread;
	m_main_ctxt = getContext();

	// Register the main thread with the SV side
	_registerThread(&m_main_thread);
}

GoogletestSvEngine::~GoogletestSvEngine() {
	// TODO Auto-generated destructor stub
}

void GoogletestSvEngine::init(const gtest_hdl::ICmdlineProcessor &clp) {
	googletest_sv_init();
}

void GoogletestSvEngine::run() {
	googletest_sv_run();
}

void GoogletestSvEngine::raiseObjection() {
	googletest_sv_raise_objection();
}

void GoogletestSvEngine::dropObjection() {
	googletest_sv_drop_objection();
}

double GoogletestSvEngine::simtime() {
	return 0.0; // TODO:
}

void GoogletestSvEngine::close() {

}

/**
 * Return the current context (ie DPI scope)
 */
void *GoogletestSvEngine::getContext() {
	return svGetScope();
}

/**
 * Set the active context (ie DPI scope)
 */
void GoogletestSvEngine::setContext(void *ctxt) {
	svSetScope(ctxt);
}

// Create a new thread
GvmThread *GoogletestSvEngine::createThread() {
	// TODO:
	return 0;
}

// Return the currently-active thread
GvmThread *GoogletestSvEngine::activeThread() {
	return m_active_thread;
}

// Block the specified thread
void GoogletestSvEngine::blockThread(GvmThread *t) {
	fprintf(stdout, "blockThread\n");
	setContext(m_main_ctxt);
	_blockThread(t);
}

// Unblock the specified thread
void GoogletestSvEngine::unblockThread(GvmThread *t) {
	fprintf(stdout, "unblockThread\n");
	setContext(m_main_ctxt);
	_unblockThread(t);
}

// Yield the active thread
void GoogletestSvEngine::yieldThread() {
	fprintf(stdout, "yieldThread\n");
	setContext(m_main_ctxt);
	_yieldThread();
}

