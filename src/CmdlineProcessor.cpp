/*
 * CmdlineProcessor.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */

#include <stdio.h>

#include "CmdlineProcessor.h"

using namespace gtest_hdl;

CmdlineProcessor::CmdlineProcessor() {
}

CmdlineProcessor::CmdlineProcessor(int argc, char **argv) {
	init(argc, argv);
}

CmdlineProcessor::~CmdlineProcessor() {
	// TODO Auto-generated destructor stub
}

void CmdlineProcessor::init(int argc, char **argv) {
	m_plusargs.clear();
	m_args.clear();

	for (int i=0; i<argc; i++) {
		if (argv[i][0] == '+') {
			m_plusargs.push_back(argv[i]);
		}
		m_args.push_back(argv[i]);
	}
}

bool CmdlineProcessor::get_plusarg_values(const std::string &plusarg, std::vector<std::string> &values) const {
	bool ret = false;
	for (std::vector<std::string>::const_iterator it=m_plusargs.begin();
			it!=m_plusargs.end(); it++) {
		int i=0;

		while (i<plusarg.size() && i<it->size() && plusarg.at(i) == it->at(i)) {
			i++;
		}
		if (i == plusarg.size() && it->at(i) == '=') {
			fprintf(stdout, "plusarg %s matches pattern %s\n", it->c_str(), plusarg.c_str());
			values.push_back(it->substr(i+1));
		}
		ret = true;
	}

	return ret;
}

bool CmdlineProcessor::get_plusarg_value(const std::string &plusarg, std::string &value) const {
	std::vector<std::string> values;
	get_plusarg_values(plusarg, values);

	if (values.size() > 0) {
		value = values.at(0);
	}

	return values.size() > 0;
}

bool CmdlineProcessor::has_plusarg(const std::string &plusarg) const {

	for (std::vector<std::string>::const_iterator it=m_plusargs.begin();
			it!=m_plusargs.end(); it++) {
		if ((*it) == plusarg) {
			return true;
		}
	}

	return false;
}

