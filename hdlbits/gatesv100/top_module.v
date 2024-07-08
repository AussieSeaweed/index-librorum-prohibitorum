module top_module (
	input [99:0] in,
	output [98:0] out_both,
	output [99:1] out_any,
	output [99:0] out_different
);

	genvar i;

	generate
		assign out_both[0] = &in[1:0];
		assign out_different[0] = ^in[1:0];

		for (i = 1; i < 99; i = i + 1) begin : operation
			assign out_both[i] = &in[i + 1:i];
			assign out_any[i] = |in[i:i - 1];
			assign out_different[i] = ^in[i + 1:i];
		end

		assign out_any[99] = |in[99:98];
		assign out_different[99] = in[99] ^ in[0];
	endgenerate

endmodule
