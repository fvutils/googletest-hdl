/*
 * BFMTypeBase.h
 *
 *  Created on: Dec 1, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_BFM_TYPE_BASE_H
#define INCLUDED_BFM_TYPE_BASE_H
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

class BfmBase;
class BfmTypeBase {
public:
	BfmTypeBase();

	virtual ~BfmTypeBase();

	virtual BfmBase *create(const std::string &path) = 0;

protected:

	BfmBase *get_bfm(uint32_t id);

	BfmBase *get_bfm(const std::string &path);

	uint32_t add_bfm(const std::string &path, BfmBase *bfm);

private:
	std::vector<BfmBase *>				m_bfm_list;
	std::map<std::string, uint32_t>		m_inst_map;
};

#endif /* INCLUDED_BFM_TYPE_BASE_H */
