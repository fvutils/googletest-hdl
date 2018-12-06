/*
 * Bfm.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_BFM_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_BFM_H_
#include <string>
#include "BfmBase.h"
#include "BfmType.h"

template <class RSP> class Bfm : public BfmBase {
public:
	Bfm() : m_rsp_if(0) {

	};

	virtual ~Bfm() { };

	void set_rsp_if(RSP *rsp_if) { m_rsp_if = rsp_if; }

	RSP *get_rsp_if() const { return m_rsp_if; }

protected:
	RSP									*m_rsp_if;
};

#define bfm_type_decl(name) \
	extern "C" int unsigned name ## _register(const char *path) { \
	}

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_BFM_H_ */
