module top_module (
	input clk,
	input areset,
	input x,
	output z
);

	reg [2:0] state, next_state;

	always @(*)
		next_state = {next_state[1] ^ state[1], state[1] | x, x};

	always @(posedge clk, posedge areset)
		state <= areset ? 3'b000 : next_state;

	assign z = ^state;

endmodule
