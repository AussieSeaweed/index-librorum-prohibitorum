module top_module (
	input [3:0] SW,
	input [3:0] KEY,
	output [3:0] LEDR
);

	wire [3:0] R, Q;
	wire clk, E, L, w;

	assign R = SW;
	assign {w, L, E, clk} = KEY;
	assign LEDR = Q;

	MUXDFF m3(clk, w, E, L, R[3], Q[3]);
	MUXDFF m2(clk, Q[3], E, L, R[2], Q[2]);
	MUXDFF m1(clk, Q[2], E, L, R[1], Q[1]);
	MUXDFF m0(clk, Q[1], E, L, R[0], Q[0]);

endmodule

module MUXDFF (
	input clk,
	input d,
	input E,
	input L,
	input R,
	output Q
);

	wire D = L ? R : (E ? d : Q);

	always @(posedge clk)
		Q <= D;

endmodule
