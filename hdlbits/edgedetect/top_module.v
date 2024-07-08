module top_module (
	input clk,
	input [7:0] in,
	output reg [7:0] pedge
);

	reg [7:0] pin;

	always @(posedge clk) begin
		pedge <= (pin ^ in) & in;
		pin <= in;
	end

endmodule
