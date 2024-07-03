module top_module (
	input clk,
	input load,
	input [511:0] data,
	output [511:0] q
);
	genvar i;

	generate
		for (i = 0; i < 512; i = i + 1) begin : rule
			rule90 ri(
				clk,
				load,
				i == 511 ? 1'b0 : q[i + 1],
				q[i],
				i ? q[i - 1] : 1'b0,
				data[i],
				q[i]
			);
		end
	endgenerate

endmodule

module rule90 (
	input clk,
	input reset,
	input l,
	input c,
	input r,
	input d,
	output reg q
);

	always @(posedge clk)
		if (reset)
			q <= d;
		else
			case ({l, c, r})
				3'b111, 3'b101, 3'b010, 3'b000:
					q <= 1'b0;
				3'b110, 3'b100, 3'b011, 3'b001:
					q <= 1'b1;
				default:
					$fatal;
			endcase

endmodule
