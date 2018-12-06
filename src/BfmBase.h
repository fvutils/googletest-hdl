/*
 * BfmBase.h
 *
 *  Created on: Dec 4, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_HDL_SRC_BFMBASE_H_
#define PACKAGES_GOOGLETEST_HDL_SRC_BFMBASE_H_
#include <string>

class BfmBase {
public:
	BfmBase();

	virtual ~BfmBase();

	void init(
			const std::string 	&path,
			void				*ctxt);

};

#endif /* PACKAGES_GOOGLETEST_HDL_SRC_BFMBASE_H_ */
