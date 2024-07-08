module top_module (
	input clk,
	input reset,
	input [31:0] in,
	output [31:0] out
);

	reg [31:0] pin;

	always @(posedge clk) begin
		out <= {32{~reset}} & (out | ((in ^ pin) & ~in));
		pin <= in;
	end

endmodule
