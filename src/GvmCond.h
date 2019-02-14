/*
 * GvmCond.h
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */
#pragma once
#include <vector>
class GvmMutex;
class GvmThread;

class GvmCond {
public:
	GvmCond();

	virtual ~GvmCond();

	void wait(GvmMutex &mutex);

	void notify();

	void notify_all();

private:
	std::vector<GvmThread *>		m_notify_list;


};

