module top_module (
	input clk,
	input d, 
	input r,
	output q
);

	always @(posedge clk)
		q <= r ? 1'b0 : d;

endmodule
