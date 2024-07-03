module top_module (
	input clk,
	input reset,
	input [7:0] d,
	output [7:0] q
);

	always @(posedge clk)
		q <= reset ? 8'b0 : d;

endmodule
