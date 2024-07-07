module top_module (
	input clk,
	input aresetn,
	input x,
	output z
);

	reg [1:0] state, next_state;

	always @(*)
		next_state = {state[0], x};

	always @(posedge clk, negedge aresetn)
		state <= ~aresetn ? 3'b000 : next_state;

	assign z = (state == 2'b10) & x;

endmodule
