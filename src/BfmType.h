/*
 * BFMType.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_BFM_TYPE_H
#define INCLUDED_BFM_TYPE_H
#include <stdint.h>
#include "BfmTypeBase.h"

class BfmBase;

template <class T> class BfmType : public BfmTypeBase {
public:

	BfmType() {
		if (!m_type) {
			m_type = this;
		}
	}

	virtual BfmBase *create(const std::string &path) {
		return new T();
	}

	static BfmTypeBase *get_type() { return m_type; }

	static T *bfm(uint32_t id) { return static_cast<T *>(m_type->get_bfm(id)); }

	static T *bfm(const std::string &path) { return static_cast<T *>(m_type->get_bfm(path)); }

	static uint32_t register_bfm(const std::string &path);

private:
	static BfmType<T>				*m_type;

};

template <class T> uint32_t BfmType<T>::register_bfm(const std::string &path) {
	T *bfm = new T();
	uint32_t ret = m_type->add_bfm(path, bfm);

	return ret;

}

template <class T> BfmType<T> *BfmType<T>::m_type = 0;



#endif /* INCLUDED_BFM_TYPE_H */
