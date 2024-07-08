module top_module (
	input x,
	input y,
	output z
);

	wire z0, z1, z2, z3;

	a a0(x, y, z0);
	a b0(x, y, z1);
	b a1(x, y, z2);
	b b1(x, y, z3);

	assign z = (z0 | z1) ^ (z2 & z3);

endmodule


module a (
	input x,
	input y,
	output z
);

	assign z = (x ^ y) & x;

endmodule


module b (
	input x,
	input y,
	output z
);

	assign z = x == y;

endmodule
