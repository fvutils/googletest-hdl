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
#include "GoogletestHdlTestListener.h"
#include "GoogletestHdlCmdlineProcessor.h"
#include "FilelistParser.h"
#include "verilated.h"
#include "verilated_lxt2_c.h"
#include "gtest/gtest.h"
#include <unistd.h>

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


	// TODO: must expand out any filelists

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

	GoogletestHdlCmdlineProcessor::init(new_argc, new_argv);

	std::string filter;
	if (GoogletestHdlCmdlineProcessor::instance().get_plusarg_value("+gtest-filter", filter)) {
		::testing::GTEST_FLAG(filter) = filter.c_str();
	}

    ::testing::TestEventListeners &listeners =
                     ::testing::UnitTest::GetInstance()->listeners();
     listeners.Append(GoogletestHdlTestListener::inst());

	Verilated::commandArgs(argc, argv);

	int ret = RUN_ALL_TESTS();

	std::string testname = "UNSPECIFIED";
	GoogletestHdlCmdlineProcessor::instance().get_plusarg_value("+TESTNAME", testname);

	GoogletestHdlTestListener *listener = GoogletestHdlTestListener::inst();
	if (listener->num_passed() && !listener->num_failed()) {
		fprintf(stdout, "PASSED: %s\n", testname.c_str());
	} else if (listener->num_failed()) {
		fprintf(stdout, "FAILED: %s (%d errors)\n", testname.c_str(), listener->num_failed());
	} else {
		fprintf(stdout, "FAILED: %s (no tests run)\n", testname.c_str());
	}

	return ret;
}



