module top_module (
	input clk,
	input resetn,
	input in,
	output out
);

	wire [3:0] d, q;

	assign d[3] = in;
	assign d[2:0] = q[3:1];
	assign out = q[0];

	always @(posedge clk)
		q <= resetn ? d : 4'h0;


endmodule
