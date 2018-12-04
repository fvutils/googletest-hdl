/*
 * IEngine.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_IENGINE_H
#define INCLUDED_IENGINE_H

namespace gtest_hdl {
class IEngine {
public:

	virtual ~IEngine() { }

	virtual void run() = 0;

	virtual void raiseObjection() = 0;

	virtual void dropObjection() = 0;

	virtual double simtime() = 0;

//	virtual std::string testname() const = 0;

};

}


#endif /* INCLUDED_IENGINE_H */
