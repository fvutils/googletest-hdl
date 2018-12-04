/*
 * GoogletestVlEngine.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_VL_ENGINE_H
#define INCLUDED_GOOGLETEST_VL_ENGINE_H
#include "GoogletestVlEngineFactory.h"
#include "GoogletestVlEngineBase.h"
#include <stdio.h>

using namespace gtest_hdl;

template <class T> class GoogletestVlEngine : public GoogletestVlEngineBase {
public:

	GoogletestVlEngine() {
		m_top = new T();
	}

	virtual ~GoogletestVlEngine() { }

protected:

	virtual void eval() { m_top->eval(); m_var++; }

	virtual void trace() { m_top->trace(0, 99); }

	T *top() const { return m_top; }

	GoogletestVlEngineFactoryBase *factory() { return m_factory; }

private:
	static GoogletestVlEngineFactory<T>					m_factory;
	static uint32_t										m_var;
	T													*m_top;

};

uint32_t var_init() {
	fprintf(stdout, "var_init\n");
	fflush(stdout);

	return 25;
}

template <class T> GoogletestVlEngineFactory<T> 	GoogletestVlEngine<T>::m_factory;
template <class T> uint32_t GoogletestVlEngine<T>::m_var = var_init();

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_VL_GOOGLETESTVLENGINE_H_ */
