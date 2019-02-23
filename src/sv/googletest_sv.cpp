/****************************************************************************
 * googletest_sv.cpp
 ****************************************************************************/
#include "gtest/gtest.h"
#include <stdint.h>
#include <string>
#include <stdarg.h>
#include <stdio.h>

#include "CmdlineProcessor.h"
#include "GoogletestHdl.h"
#include "GoogletestSvEngine.h"

static std::string		prv_filter;
static void				*prv_scope = 0;

#ifdef __cplusplus
extern "C" {
#endif

void *svGetScope();
void svSetScope(void *s);

typedef enum {
	TYPE_NOTE,
	TYPE_WARN,
	TYPE_ERROR,
	TYPE_FATAL
} googletest_sv_msg_t;

void _googletest_sv_report(const char *msg, int t);
int _googletest_sv_init(void);
int _googletest_sv_run(void);
int _googletest_sv_raise_objection(void);
int _googletest_sv_drop_objection(void);
int _googletest_sv_num_tests(void);
int _googletest_sv_num_passed(void);
int _googletest_sv_num_failed(void);

namespace googletest_sv {

class TestListener : public ::testing::EmptyTestEventListener {
public:
	TestListener() {
		m_buf_len = 1024;
		m_buf = new char [m_buf_len];
		m_num_tests = 0;
	}

	virtual void OnTestStart(const ::testing::TestInfo &test_info) {
		m_test_case_name = test_info.test_case_name();
		m_test_name = test_info.name();
		m_num_tests++;
		msg(TYPE_NOTE, "OnTestStart");
	}

	virtual void OnTestPartResult(const ::testing::TestPartResult &result) {
		if (result.failed()) {
			msg(TYPE_ERROR,
					"Test Failed: %s.%s @ %s:%d (%s)",
					m_test_case_name.c_str(),
					m_test_name.c_str(),
					result.file_name(),
					result.line_number(),
					result.summary());
		} else {
			msg(TYPE_NOTE,
					"Test Passed: %s.%s @ %s:%d (%s)",
					m_test_case_name.c_str(),
					m_test_name.c_str(),
					result.file_name(),
					result.line_number(),
					result.summary());
		}
	}

	virtual void OnTestEnd(const ::testing::TestInfo &test_info) {
		const ::testing::TestResult *test_result = test_info.result();

		if (test_result->Passed()) {
			msg(TYPE_NOTE,
					"Test Passed: %s.%s",
					test_info.test_case_name(),
					test_info.name());
		} else {
			msg(TYPE_ERROR,
					"Test Failed: %s.%s",
					test_info.test_case_name(),
					test_info.name());
		}
	}

	void msg(int t, const char *fmt, ...) {
		va_list ap;
		va_start(ap, fmt);

		vsnprintf(m_buf, m_buf_len, fmt, ap);

		fprintf(stdout, "--> svSetScope %p\n", prv_scope);
		svSetScope(prv_scope);
		fprintf(stdout, "<-- svSetScope %p\n", prv_scope);
		fprintf(stdout, "--> googletest_sv_report\n");
		_googletest_sv_report(m_buf, t);
		fprintf(stdout, "<-- googletest_sv_report\n");

		va_end(ap);
	}

	uint32_t num_tests() const { return m_num_tests; }

private:

	std::string			m_test_case_name;
	std::string			m_test_name;

	char				*m_buf;
	uint32_t			m_buf_len;
	uint32_t			m_num_tests;
};

}

extern "C" int acc_fetch_argc(void);
extern "C" char **acc_fetch_argv(void);

void _googletest_sv_set_test_filter(const char *filter) {
	prv_filter = filter;
	::testing::GTEST_FLAG(filter) = prv_filter.c_str();
}

void googletest_sv_init() {
	svSetScope(prv_scope);
	if (!_googletest_sv_init()) {
		// TODO:
	}
}

void googletest_sv_run(double time_ns) {
	svSetScope(prv_scope);
	if (!_googletest_sv_run()) {
		// TODO:
	}
}

void googletest_sv_raise_objection(void) {
	svSetScope(prv_scope);
	if (_googletest_sv_raise_objection()) {
		// TODO:
	}
}

void googletest_sv_drop_objection(void) {
	fprintf(stdout, "--> googletest_sv_drop_objection()\n");
	fflush(stdout);
	svSetScope(prv_scope);
	if (_googletest_sv_drop_objection()) {
		// TODO:
	}
	fprintf(stdout, "<-- googletest_sv_drop_objection()\n");
	fflush(stdout);
}

/********************************************************************
 * _googletest_sv_main()
 *
 * Main routine called from the simulation to run a GoogleTest
 ********************************************************************/
int _googletest_sv_main(void) {
	int argc = acc_fetch_argc();
	char **argv = acc_fetch_argv();
	int status;
	GoogletestSvEngine		*engine = new GoogletestSvEngine();

	fprintf(stdout, "googletest_sv_main()\n");

	// Capture the scope
	prv_scope = svGetScope();


	testing::InitGoogleTest(&argc, argv);

	GoogletestHdl::inst().init(
			argc,
			argv,
			engine);

	std::string filter;
	const CmdlineProcessor &clp = GoogletestHdl::inst().clp();
	if (clp.get_plusarg_value("+gtest-filter", filter)) {
		::testing::GTEST_FLAG(filter) = filter.c_str();
	}

	status = RUN_ALL_TESTS();

	GoogletestHdl &inst = GoogletestHdl::inst();
	if (inst.num_tests() == 0) {
		// TODO:
//		l->msg(TYPE_FATAL, "No tests selected");
	}

	delete engine;

	return 0;
}

int _googletest_sv_num_tests(void) {
	return GoogletestHdl::inst().num_tests();
}
int _googletest_sv_num_passed(void) {
	return GoogletestHdl::inst().num_passed();
}

int _googletest_sv_num_failed(void) {
	return GoogletestHdl::inst().num_failed();
}

#ifdef __cplusplus
}
#endif
