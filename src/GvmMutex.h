/*
 * GvmMutex.h
 *
 *  Created on: Feb 6, 2019
 *      Author: ballance
 */
#pragma once
class GvmThread;

class GvmMutex {
public:
	GvmMutex();

	virtual ~GvmMutex();

	void lock();

	void unlock();

private:
	GvmThread			*m_owner;
	GvmThread			*m_block_list;

};

