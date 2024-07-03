module top_module (
	input clk,
	input reset,
	output [3:1] ena,
	output [15:0] q
);

	bcdc bcdc0(clk, reset, 1'b1, q[3:0]);
	bcdc bcdc1(clk, reset, ena[1], q[7:4]);
	bcdc bcdc2(clk, reset, ena[2], q[11:8]);
	bcdc bcdc3(clk, reset, ena[3], q[15:12]);

	assign ena[1] = q[3] & q[0];
	assign ena[2] = q[7] & q[4] & ena[1];
	assign ena[3] = q[11] & q[8] & ena[2];

endmodule

module bcdc (
	input clk,
	input reset,
	input ena,
	output reg [3:0] q
);

	always @(posedge clk)
		if (ena | reset)
			q <= reset | (q == 4'h9) ? 4'h0 : q + 4'h1;

endmodule
