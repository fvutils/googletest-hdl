/*
 * Bfm.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */
#pragma once
#include <string>
#include "GvmBfmBase.h"
#include "GvmBfmType.h"

template <class RSP> class GvmBfm : public GvmBfmBase {
public:
	GvmBfm(RSP *rsp_if=0) : m_rsp_if(rsp_if) {

	};

	virtual ~GvmBfm() { };

	void set_rsp_if(RSP *rsp_if) { m_rsp_if = rsp_if; }

	RSP *get_rsp_if() const { return m_rsp_if; }

protected:
	RSP									*m_rsp_if;
};

#define bfm_type_decl(name) \
	extern "C" int unsigned name ## _register(const char *path) { \
	}

