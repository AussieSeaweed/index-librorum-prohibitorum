module top_module (
	input [31:0] a,
	input [31:0] b,
	input sub,
	output [31:0] sum
);

	wire c;
	wire [31:0] d;

	assign d = {32{sub}} ^ b;

	add16 add160(.a(a[15:0]), .b(d[15:0]), .cin(sub), .sum(sum[15:0]), .cout(c));
	add16 add161(.a(a[31:16]), .b(d[31:16]), .cin(c), .sum(sum[31:16]));

endmodule
