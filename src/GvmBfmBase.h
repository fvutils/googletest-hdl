/*
 * GvmBfmBase.h
 *
 *  Created on: Dec 4, 2018
 *      Author: ballance
 */
#pragma once
#include <string>

class GvmBfmBase {
public:
	GvmBfmBase();

	virtual ~GvmBfmBase();

	virtual void init(
			const std::string 	&path,
			void				*ctxt);

	void *getContext() const { return m_ctxt; }

private:
	std::string					m_path;
	void						*m_ctxt;

};

