/*
 * CmdlineProcessor.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR
#define INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR
#include <vector>
#include <string>
#include "ICmdlineProcessor.h"

namespace gtest_hdl {
class CmdlineProcessor : public virtual ICmdlineProcessor {
public:
	CmdlineProcessor();

	CmdlineProcessor(int argc, char **argv);

	virtual ~CmdlineProcessor();

	void init(int argc, char **argv);

	virtual const std::vector<std::string> &get_args() const { return m_args; }

	virtual const std::vector<std::string> &get_plusargs() const { return m_plusargs; }

	// Returns all plusargs that match the specified plusarg
	// plusarg="+OPTION" => returns all
	virtual bool get_plusarg_values(const std::string &plusarg, std::vector<std::string> &values) const;

	// Returns the first plusarg that matches the specified
	virtual bool get_plusarg_value(const std::string &plusarg, std::string &value) const;

	virtual bool has_plusarg(const std::string &plusarg) const;

protected:



private:
	std::vector<std::string>			m_args;
	std::vector<std::string>			m_plusargs;
};
}

#endif /* INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR */
