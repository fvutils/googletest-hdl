/*
 * googletest_vl_main.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: ballance
 */
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>
#include "GoogletestHdl.h"
#include "GoogletestHdl.h"
#include "GoogletestHdl.h"
#include "GoogletestHdl.h"
#include "GoogletestVlEngineRegistry.h"
#include "FilelistParser.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include "gtest/gtest.h"
#include <unistd.h>
#include "CmdlineProcessor.h"
#include "GvmException.h"

int main(int argc, char **argv) {
	bool trace = true;
	char cwd[1024];
	std::vector<std::string> args;

	getcwd(cwd, sizeof(cwd));

	for (int i=1; i<argc; i++) {
		if (!strcasecmp(argv[i], "-f")) {
			std::string filelist = argv[i+1];
			if (!FilelistParser::parse(filelist, cwd, !strcmp(argv[i], "-F"), args)) {
				// TODO: handle error
				fprintf(stdout, "Error: parse error\n");
			}
			i++;
		} else {
			args.push_back(argv[i]);
		}
	}

	if (trace) {
		Verilated::traceEverOn(true);
	}

	char **new_argv = new char *[args.size()+1];
	for (int i=0; i<args.size(); i++) {
		new_argv[i] = strdup(args.at(i).c_str());
	}
	new_argv[args.size()] = 0;
	int new_argc = args.size();

	::testing::InitGoogleTest(&new_argc, new_argv);

	Verilated::commandArgs(new_argc, new_argv);

	GoogletestVlEngineFactoryBase *engine_f = GoogletestVlEngineRegistry::inst().get_default();
	IEngine *engine = engine_f->create();

	GoogletestHdl::init(new_argc, new_argv, engine);
	const CmdlineProcessor &clp = GoogletestHdl::inst().clp();

	std::string filter;
	if (clp.get_plusarg_value("+gtest-filter", filter)) {
		::testing::GTEST_FLAG(filter) = filter.c_str();
	}

	int ret = -1;
	bool exception = false;
	std::string msg;

	try {
		ret = RUN_ALL_TESTS();
	} catch (GvmException &e) {
		exception = true;
		msg = e.msg();
	}

	engine->close();

	std::string testname = "UNSPECIFIED";
	if (!clp.get_plusarg_value("+TESTNAME", testname)) {
		fprintf(stdout, "Error: +TESTNAME not specified\n");
	}

	GoogletestHdl &inst = GoogletestHdl::inst();

	if (exception) {
		fprintf(stdout, "FAILED: %s (exception: %s)\n", testname.c_str(), msg.c_str());
	} else if (inst.num_passed() && inst.num_failed() == 0) {
		fprintf(stdout, "PASSED: %s\n", testname.c_str());
	} else if (inst.num_failed()) {
		fprintf(stdout, "FAILED: %s (%d errors)\n", testname.c_str(), inst.num_failed());
	} else {
		fprintf(stdout, "FAILED: %s (no tests run)\n", testname.c_str());
	}

	return ret;
}



