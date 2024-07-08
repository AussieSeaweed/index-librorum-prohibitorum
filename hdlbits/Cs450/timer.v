module top_module (
	input clk,
	input load,
	input [9:0] data,
	output tc
);

	reg [9:0] counter;

	always @(posedge clk)
		counter = load ? data : (|counter ? counter - 10'd1 : 10'd0);

	assign tc = ~|counter;

endmodule
