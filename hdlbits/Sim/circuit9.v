module top_module (
	input clk,
	input a,
	output [3:0] q
);

	always @(posedge clk)
		q <= a ? 4'd4 : (q + 4'd1) % 4'd7;

endmodule
