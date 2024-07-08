module top_module ();

	reg clk, reset, t;
	wire q;

	tff tff(clk, reset, t, q);

	initial
		clk = 1'b0;

	always
		#5 clk = ~clk;

	initial begin
		reset = 1'b1;
		#10 reset = 1'b0;
	end

	initial begin
		t = 1'b0;
		#20 t = 1'b1;
	end

endmodule
