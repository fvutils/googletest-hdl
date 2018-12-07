/****************************************************************************
 * googletest_sv_pkg.sv
 ****************************************************************************/

/**
 * Package: googletest_sv_pkg
 * 
 * TODO: Add package documentation
 */
package googletest_sv_pkg;
	

	int						prv_objections = 0;
	event					prv_objections_e;
	
	task automatic _googletest_sv_raise_objection();
		prv_objections++;
		-> prv_objections_e;
	endtask
	export "DPI-C" task _googletest_sv_raise_objection;
	
	task automatic _googletest_sv_drop_objection();
		if (prv_objections > 0) begin
			prv_objections--;
		end
		-> prv_objections_e;
	endtask
	export "DPI-C" task _googletest_sv_drop_objection;
	
	task automatic _googletest_sv_run();
		do begin
			#0;
			if (prv_objections > 0) begin
				@prv_objections_e;
			end
		end while (prv_objections > 0);
	endtask
	export "DPI-C" task _googletest_sv_run;
	
	function void _googletest_sv_report(
		string			msg,
		int				t);
		case (t)
			0: begin
				$display("INFO: %0s", msg);
			end
			1: begin
				$display("WARN: %0s", msg);
			end
			2: begin
				$display("ERROR: %0s", msg);
			end
			3: begin
				$display("FATAL: %0s", msg);
			end
		endcase
	endfunction
	export "DPI-C" function _googletest_sv_report;
	
	import "DPI-C" context function int _googletest_sv_num_tests();
	import "DPI-C" context function int _googletest_sv_num_passed();
	import "DPI-C" context function int _googletest_sv_num_failed();
	
	task automatic _googletest_sv_init();
		repeat (10) begin
			#0;
		end
	endtask
	export "DPI-C" task _googletest_sv_init;

	/**
	 * Task: run_all_tests
	 * 
	 * Task description needed
	 * 
	 * Parameters:
	 * - string filter 
	 */
	task automatic run_all_tests();
		string testname;
		int num_tests, num_passed, num_failed;
		_googletest_sv_main();
		
		// Report test status
		if (!$value$plusargs("TESTNAME=%s", testname)) begin
			$display("Error: +TESTNAME not specified");
			testname = "UNNAMED";
		end
		num_tests = _googletest_sv_num_tests();
		num_passed = _googletest_sv_num_passed();
		num_failed = _googletest_sv_num_failed();
		if (num_passed > 0 && num_failed == 0) begin
			$display("PASSED: %0s", testname);
		end else if (num_failed > 0) begin
			$display("FAILED: %0s (%0d errors)", testname, num_failed);
		end else begin
			$display("FAILED: %0s (no tests run)", testname);
		end
		$finish();
	endtask
	import "DPI-C" context task _googletest_sv_main();

endpackage


