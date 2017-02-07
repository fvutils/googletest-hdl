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
	
	import "DPI-C" function void _googletest_uvm_set_test_filter(string filter);
	
	import "DPI-C" context task _googletest_uvm_main();
	
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
	
	task automatic run_all_tests(string filter="");
		_googletest_uvm_set_test_filter(filter);
		_googletest_uvm_main();
	endtask

endpackage


