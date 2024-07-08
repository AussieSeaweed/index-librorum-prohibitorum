module top_module (
	input clk,
	input areset,
	input bump_left,
	input bump_right,
	input ground,
	output walk_left,
	output walk_right,
	output aaah
);

	parameter LEFT = 2'b00, RIGHT = 2'b01, LEFT_FALLING = 2'b10, RIGHT_FALLING = 2'b11;
	reg [1:0] state, next_state;

	always @(*)
		case (state)
			LEFT:
				next_state = ground ? (bump_left ? RIGHT : LEFT) : LEFT_FALLING;
			RIGHT:
				next_state = ground ? (bump_right ? LEFT : RIGHT) : RIGHT_FALLING;
			LEFT_FALLING:
				next_state = ground ? LEFT : LEFT_FALLING;
			RIGHT_FALLING:
				next_state = ground ? RIGHT : RIGHT_FALLING;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		state <= areset ? LEFT : next_state;

	assign walk_left = state == LEFT;
	assign walk_right = state == RIGHT;
	assign aaah = (state == LEFT_FALLING) | (state == RIGHT_FALLING);

endmodule
