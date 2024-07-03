module top_module (
	input [399:0] a, b,
	input cin,
	output cout,
	output [399:0] sum
);

	wire [99:0] c;

	bcd_fadd ba0(a[3:0], b[3:0], cin, c[0], sum[3:0]);

	genvar i;

	generate
		for (i = 1; i < 100; i = i + 1) begin : addition
			localparam integer j = 4 * i;
			localparam integer k = j + 3;

			bcd_fadd ba(a[k:j], b[k:j], c[i - 1], c[i], sum[k:j]);
		end
	endgenerate

	assign cout = c[99];

endmodule
