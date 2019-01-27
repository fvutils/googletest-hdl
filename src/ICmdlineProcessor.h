/*
 * ICmdlineProcessor.h
 *
 *  Created on: Dec 9, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_ICMDLINE_PROCESSOR_H
#define INCLUDED_ICMDLINE_PROCESSOR_H
#include <vector>
#include <string>

namespace gtest_hdl {
class ICmdlineProcessor {
public:

	virtual ~ICmdlineProcessor() { }

	virtual const std::vector<std::string> &get_args() const  = 0;

	virtual const std::vector<std::string> &get_plusargs() const  = 0;

	virtual bool get_plusarg_values(const std::string &plusarg, std::vector<std::string> &values) const = 0;

	virtual bool get_plusarg_value(const std::string &plusarg, std::string &value) const = 0;

	virtual bool has_plusarg(const std::string &plusarg) const = 0;

};
}

#endif /* INCLUDED_ICMDLINE_PROCESSOR_H */
