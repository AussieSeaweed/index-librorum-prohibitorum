module top_module (
	input clk,
	input shift_ena,
	input count_ena,
	input data,
	output [3:0] q
);

	reg [3:0] state, next_state;

	always @(*)
		if (shift_ena)
			next_state = {state[2:0], data};
		else if (count_ena)
			next_state = state - 4'b1;
		else
			next_state = state;

	always @(posedge clk)
		state <= next_state;

	assign q = state;

endmodule
