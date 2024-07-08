module top_module (
	input clock,
	input a,
	output p,
	output reg q
);

	assign p = clock ? a : q;

	always @(negedge clock)
		q <= a;

endmodule
