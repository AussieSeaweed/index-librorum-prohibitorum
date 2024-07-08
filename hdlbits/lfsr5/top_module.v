module top_module (
	input clk,
	input reset,
	output [4:0] q
); 

	dffr dffr5(clk, q[0] ^ 0, reset, 1'b0, q[4]);
	dffr dffr4(clk, q[4], reset, 1'b0, q[3]);
	dffr dffr3(clk, q[0] ^ q[3], reset, 1'b0, q[2]);
	dffr dffr2(clk, q[2], reset, 1'b0, q[1]);
	dffr dffr1(clk, q[1], reset, 1'b1, q[0]);

endmodule

module dffr (
	input clk,
	input d,
	input reset,
	input rd,
	output reg q
);

	always @(posedge clk)
		q <= reset ? rd : d;

endmodule
