/*
 * GoogletestVlEngineFactory.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_VL_ENGINE_FACTORY_H
#define INCLUDED_GOOGLETEST_VL_ENGINE_FACTORY_H
#include "GoogletestVlEngineFactoryBase.h"
#include <typeinfo>

template <class T> class GoogletestVlEngineFactory : public GoogletestVlEngineFactoryBase {
public:
	GoogletestVlEngineFactory();

	virtual ~GoogletestVlEngineFactory() { }

	virtual IEngine *create() const { return new T(); }

};

template <class T> GoogletestVlEngineFactory<T>::GoogletestVlEngineFactory() :
		GoogletestVlEngineFactoryBase(typeid(T)) {
}

#endif /* INCLUDED_GOOGLETEST_VL_ENGINE_FACTORY_H */
