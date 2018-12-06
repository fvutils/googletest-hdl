/*
 * GvmException.h
 *
 *  Created on: Dec 4, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_GVMEXCEPTION_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_GVMEXCEPTION_H_
#include <string>
#include <exception>

class GvmException : public std::exception {
public:
	GvmException(const std::string &msg);

	virtual ~GvmException();

	const std::string &msg() const { return m_msg; }

private:
	std::string				m_msg;
};

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_GVMEXCEPTION_H_ */
