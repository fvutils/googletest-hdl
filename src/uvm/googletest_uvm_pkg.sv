/****************************************************************************
 * googletest_uvm_pkg.sv
 ****************************************************************************/
`include "uvm_macros.svh"

/**
 * Package: googletest_uvm_pkg
 * 
 * TODO: Add package documentation
 */
package googletest_uvm_pkg;
	import uvm_pkg::*;
	
	class googletest_uvm_test extends uvm_test;
		`uvm_component_utils(googletest_uvm_test);
		
		function new(string name, uvm_component parent=null);
			super.new(name, parent);
		endfunction
		
		task run_phase(uvm_phase phase);
			phase.raise_objection(this, "GoogleTest");
			run_all_tests();
			phase.drop_objection(this, "GoogleTest");
		endtask
		
		function void report_phase(uvm_phase phase);
			string testname;
		
			// Only report a message if TESTNAME is set
			if ($value$plusargs("TESTNAME=%s", testname)) begin
				
				$display("PASSED: %0s", testname);
			end
			
		endfunction
	endclass
	
	import "DPI-C" context function int _googletest_uvm_init();
	int _init = _googletest_uvm_init();
	
	import "DPI-C" function void _googletest_uvm_set_test_filter(string filter);
	
	import "DPI-C" context task _googletest_uvm_main();

	int						prv_objections = 0;
	event					prv_objections_e;
	
	task automatic _googletest_uvm_raise_objection();
		prv_objections++;
		-> prv_objections_e;
	endtask
	export "DPI-C" task _googletest_uvm_raise_objection;
	
	task automatic _googletest_uvm_drop_objection();
		if (prv_objections > 0) begin
			prv_objections--;
		end
		-> prv_objections_e;
	endtask
	export "DPI-C" task _googletest_uvm_drop_objection;
	
	task automatic _googletest_uvm_run();
		$display("--> googletest_uvm_run");
		do begin
			#0;
			if (prv_objections > 0) begin
				@prv_objections_e;
			end
		end while (prv_objections > 0);
		$display("<-- googletest_uvm_run");
	endtask
	export "DPI-C" task _googletest_uvm_run;
	
	function void _googletest_uvm_report(
		string			msg,
		int				t);
		case (t)
			0: begin
				`uvm_info("googletest_uvm", msg, UVM_LOW);
			end
			1: begin
				`uvm_warning("googletest_uvm", msg);
			end
			2: begin
				`uvm_error("googletest_uvm", msg);
			end
			3: begin
				`uvm_fatal("googletest_uvm", msg);
			end
		endcase
	endfunction
	export "DPI-C" function _googletest_uvm_report;

	/**
	 * Task: run_all_tests
	 * 
	 * Task description needed
	 * 
	 * Parameters:
	 * - string filter 
	 */
	task automatic run_all_tests(string filter="");
		if (filter != "") begin
			_googletest_uvm_set_test_filter(filter);
		end
		_googletest_uvm_main();
	endtask

endpackage


