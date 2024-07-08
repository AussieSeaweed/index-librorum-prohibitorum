module top_module (
	input clk,
	input reset,
	output reg [9:0] q
);

	always @(posedge clk)
		q <= reset | (q == 10'd999) ? 10'd0 : q + 10'd1;

endmodule
