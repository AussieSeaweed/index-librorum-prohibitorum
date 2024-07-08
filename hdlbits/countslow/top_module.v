module top_module (
	input clk,
	input slowena,
	input reset,
	output [3:0] q
);

	always @(posedge clk)
		q <= reset | (slowena & (q == 4'h9)) ? 4'h0 : (slowena ? q + 4'h1 : q);

endmodule
