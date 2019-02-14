/*
 * GvmTimeoutException.h
 *
 *  Created on: Feb 10, 2019
 *      Author: ballance
 */

#pragma once
#include "GvmException.h"
#include <exception>

class GvmTimeoutException : public GvmException {
public:
	GvmTimeoutException(const std::string &msg);

	virtual ~GvmTimeoutException();
};

