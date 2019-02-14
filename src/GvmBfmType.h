/*
 * BFMType.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */

#pragma once
#include <stdint.h>
#include <stdio.h>

#include "GvmBfmTypeBase.h"

class GvmBfmBase;

template <class T> class GvmBfmType : public GvmBfmTypeBase {
public:

	GvmBfmType() {
		if (!m_type) {
			m_type = this;
		}
	}

	virtual GvmBfmBase *create(const std::string &path) {
		return new T();
	}

	static GvmBfmTypeBase *get_type() { return m_type; }

	static T *bfm(uint32_t id) { return static_cast<T *>(m_type->get_bfm(id)); }

	static T *bfm(const std::string &path) { return static_cast<T *>(m_type->get_bfm(path)); }

	static uint32_t register_bfm(const std::string &path);

private:
	static GvmBfmType<T>				*m_type;

};

template <class T> uint32_t GvmBfmType<T>::register_bfm(const std::string &path) {
	fprintf(stdout, "register_bfm: %s\n", path.c_str());
	T *bfm = new T();
	if (!m_type) {
		fprintf(stdout, "Fatal: missing BFM instantiation\n");
	}
	uint32_t ret = m_type->add_bfm(path, bfm);

	return ret;

}

template <class T> GvmBfmType<T> *GvmBfmType<T>::m_type = 0;



