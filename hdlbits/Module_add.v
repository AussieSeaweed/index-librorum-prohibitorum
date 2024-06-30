module top_module (
	input [31:0] a,
	input [31:0] b,
	output [31:0] sum
);

	wire c;

	add16 add160(.a(a[15:0]), .b(b[15:0]), .cin(0), .sum(sum[15:0]), .cout(c));
	add16 add161(.a(a[31:16]), .b(b[31:16]), .cin(c), .sum(sum[31:16]));

endmodule
