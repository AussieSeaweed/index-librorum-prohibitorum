module top_module (
	input clk,
	input reset,
	output [3:0] q
);

	always @(posedge clk)
		q <= reset | (q == 4'ha) ? 4'h1 : q + 4'h1;

endmodule
