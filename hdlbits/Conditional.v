module top_module (
	input [7:0] a, b, c, d,
	output [7:0] min
);

	wire [7:0] x, y;

	min m0(a, b, x);
	min m1(x, c, y);
	min m2(y, d, min);

endmodule

module min (
	input [7:0] in0, in1,
	output [7:0] out
);

	assign out = in0 < in1 ? in0 : in1;

endmodule
