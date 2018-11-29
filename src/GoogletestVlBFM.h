/*
 * GoogletestVlBFM.h
 *
 *  Created on: Oct 29, 2018
 *      Author: ballance
 */

#ifndef PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLBFM_H_
#define PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLBFM_H_

class GoogletestVlBFM {
public:
	GoogletestVlBFM();
	virtual ~GoogletestVlBFM();
};

#define googletest_vl_bfm_register(bfm_type) \
	extern "C" unsigned int bfm_type ## _ ## register(const char *path) { \
	}

#define googletest_vl_bfm_func0_impl(bfm_type, rtype, fname) \
	extern "C" rtype bfm_type ## _ ## fname(unsigned int id) { \
		bfm_type *bfm = bfm_type::get_bfm(id); \
		if (bfm) { \
		} \
	}

// #define googletest_vl_bfm_func1_impl(bfm_type, rtype, fname, )

#endif /* PACKAGES_GOOGLETEST_VL_SRC_GOOGLETESTVLBFM_H_ */
