module top_module (
	input clk,
	input enable,
	input S,
	input A, B, C,
	output Z
);

	wire [7:0] D, Q;

	assign D[0] = S;
	assign D[7:1] = Q[6:0];
	assign Z = Q[{A, B, C}];

	always @(posedge clk)
		if (enable)
			Q <= D;

endmodule
