module top_module (
	input [99:0] a, b,
	input cin,
	output [99:0] cout,
	output [99:0] sum
);

	full_adder fa0(a[0], b[0], cin, cout[0], sum[0]);

	genvar i;

	generate
		for (i = 1; i < 100; i = i + 1) begin : full_addition
			full_adder fa(a[i], b[i], cout[i - 1], cout[i], sum[i]);
		end
	endgenerate

endmodule

module full_adder (
	input a, b, cin,
	output cout, sum
);

	assign cout = a & b | a & cin | b & cin;
	assign sum = a ^ b ^ cin;

endmodule
