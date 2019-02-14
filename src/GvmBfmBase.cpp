/*
 * GvmBfmBase.cpp
 *
 *  Created on: Dec 4, 2018
 *      Author: ballance
 */

#include "GvmBfmBase.h"

GvmBfmBase::GvmBfmBase() : m_ctxt(0) {
	// TODO Auto-generated constructor stub

}

GvmBfmBase::~GvmBfmBase() {
	// TODO Auto-generated destructor stub
}

void GvmBfmBase::init(const std::string &path, void *ctxt) {
	m_path = path;
	m_ctxt = ctxt;
}

