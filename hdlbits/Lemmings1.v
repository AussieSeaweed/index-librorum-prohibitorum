module top_module (
	input clk,
	input areset,
	input bump_left,
	input bump_right,
	output walk_left,
	output walk_right
);

	parameter LEFT = 1'b0, RIGHT = 1'b1;
	reg state, next_state;

	always @(*)
		case (state)
			LEFT:
				next_state = bump_left ? RIGHT : LEFT;
			RIGHT:
				next_state = bump_right ? LEFT : RIGHT;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		state <= areset ? LEFT : next_state;

	assign walk_left = state == LEFT;
	assign walk_right = state == RIGHT;

endmodule
