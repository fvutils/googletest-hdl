/*
 * BfmTypeBase.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */

#include "BfmTypeBase.h"
#include <regex.h>
#include <sys/types.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <exception>

BfmTypeBase::BfmTypeBase() {
	// TODO Auto-generated constructor stub

}

BfmTypeBase::~BfmTypeBase() {
	// TODO Auto-generated destructor stub
}

BfmBase *BfmTypeBase::get_bfm(uint32_t id) {
	return m_bfm_list.at(id);
}

BfmBase *BfmTypeBase::get_bfm(const std::string &path) {
	if (m_inst_map.find(path) != m_inst_map.end()) {
		return m_bfm_list.at(m_inst_map.find(path)->second);
	} else {
		std::string pattern;

		for (uint32_t i=0; i<path.size(); i++) {
			if (path.at(i) == '*') {
				pattern.append(".*");
			} else if (path.at(i) == '.') {
				pattern.append("\\.");
			} else {
				pattern.push_back(path.at(i));
			}
		}

		BfmBase *ret = 0;
		// Slow path. Use regular expressions
		regex_t exp;

		if (regcomp(&exp, pattern.c_str(), REG_NOSUB) != 0) {
			fprintf(stdout, "Error: failed to compile regular expression \"%s\"\n", pattern.c_str());
		}

		for (std::map<std::string,uint32_t>::iterator it=m_inst_map.begin();
				it!=m_inst_map.end(); it++) {

			fprintf(stdout, "Test: %s against %s\n", it->first.c_str(), pattern.c_str());
			if (regexec(&exp, it->first.c_str(), 0, 0, 0) == 0) {
				fprintf(stdout, "Note: match %s\n", it->first.c_str());
				ret = m_bfm_list.at(it->second);
				break;
			}
		}

		regfree(&exp);
		// Create a new BFM

//		ASSERT_NE(ret, static_cast<BfmBase *>(0)) << "failed to find BFM with pattern \""; //  << pattern; //  << "\"";
		if (!ret) {
			throw std::runtime_error("failed to find BFM with pattern \"" + pattern + "\"");
		}
		return ret;
	}
	return 0;
//	return m_bfm_list.at(id);
}

uint32_t BfmTypeBase::add_bfm(const std::string &path, BfmBase *bfm) {
	uint32_t ret;

	if (m_inst_map.find(path) == m_inst_map.end()) {
		// need to add this instance
		ret = m_bfm_list.size();
		m_bfm_list.push_back(bfm);
		m_inst_map[path] = ret;
	} else {
		// The path is already registered
		ret = m_inst_map.find(path)->second;
		m_bfm_list.at(ret) = bfm;
	}

	return ret;
}

