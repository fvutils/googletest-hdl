/*
 * GoogletestHdlCmdlineProcessor.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR
#define INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR
#include <vector>
#include <string>

class GoogletestHdlCmdlineProcessor {
public:

	static void init(int argc, char **argv);

	static const GoogletestHdlCmdlineProcessor &instance();

	const std::vector<std::string> &get_args() const { return m_args; }

	const std::vector<std::string> &get_plusargs() const { return m_plusargs; }

	// Returns all plusargs that match the specified plusarg
	// plusarg="+OPTION" => returns all
	bool get_plusarg_values(const std::string &plusarg, std::vector<std::string> &values) const;

	// Returns the first plusarg that matches the specified
	bool get_plusarg_value(const std::string &plusarg, std::string &value) const;

	bool has_plusarg(const std::string &plusarg) const;

protected:

	GoogletestHdlCmdlineProcessor(int argc, char **argv);

	virtual ~GoogletestHdlCmdlineProcessor();

private:
	std::vector<std::string>					m_args;
	std::vector<std::string>					m_plusargs;
	static GoogletestHdlCmdlineProcessor			*m_instance;
};

#endif /* INCLUDED_GOOGLETEST_HDL_CMDLINE_PROCESSOR */
