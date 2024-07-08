module top_module (
	input clk,
	input reset,
	output [31:0] q
);

	genvar i;

	generate
		for (i = 31; i >= 0; i = i - 1) begin : shifting
			wire d;

			assign d = ((i == 21) | (i == 1) | (i == 0) ? q[0] : 1'b0) ^ q[(i + 1) % 32];

			dffr dffri(clk, d, reset, i ? 1'b0 : 1'b1, q[i]);
		end
	endgenerate

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
