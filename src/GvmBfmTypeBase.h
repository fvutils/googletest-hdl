/*
 * BFMTypeBase.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */
#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

class GvmBfmBase;
class GvmBfmTypeBase {
public:
	GvmBfmTypeBase();

	virtual ~GvmBfmTypeBase();

	virtual GvmBfmBase *create(const std::string &path) = 0;

protected:

	GvmBfmBase *get_bfm(uint32_t id);

	GvmBfmBase *get_bfm(const std::string &path);

	uint32_t add_bfm(const std::string &path, GvmBfmBase *bfm);

private:
	std::vector<GvmBfmBase *>				m_bfm_list;
	std::map<std::string, uint32_t>		m_inst_map;
};

