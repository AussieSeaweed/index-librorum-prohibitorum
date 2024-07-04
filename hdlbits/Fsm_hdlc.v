module top_module (
	input clk,
	input reset,
	input in,
	output disc,
	output flag,
	output err
);

	reg [7:0] state, next_state;

	always @(*)
		if (state[6:0] == 7'b1111111)
			next_state = in ? 8'b11111111 : 8'b00000000;
		else
			next_state = {state[6:0], in};

	always @(posedge clk)
		state <= reset ? 8'b00000000 : next_state;

	assign disc = state[6:0] == 7'b0111110;
	assign flag = state[7:0] == 8'b01111110;
	assign err = state[6:0] == 7'b1111111;

endmodule
