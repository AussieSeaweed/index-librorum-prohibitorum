module top_module (
	input in,
	input [3:0] state,
	output [3:0] next_state,
	output out
);

	parameter A = 2'd0, B = 2'd1, C = 2'd2, D = 2'd3;

	assign next_state[A] = (state[A] | state[C]) & ~in;
	assign next_state[B] = (state[A] | state[B] | state[D]) & in;
	assign next_state[C] = (state[B] | state[D]) & ~in;
	assign next_state[D] = state[C] & in;
	assign out = state[D];

endmodule
