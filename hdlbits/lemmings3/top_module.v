module top_module (
    input clk,
    input areset,
    input bump_left,
    input bump_right,
    input ground,
    input dig,
    output walk_left,
    output walk_right,
    output aaah,
    output digging
);

	parameter LEFT = 3'b000, RIGHT = 3'b001, LEFT_FALLING = 3'b010, RIGHT_FALLING = 3'b011, LEFT_DIGGING = 3'b100, RIGHT_DIGGING = 3'b101;
	reg [2:0] state, next_state;

	always @(*)
		case (state)
			LEFT:
				next_state = ground ? (dig ? LEFT_DIGGING : (bump_left ? RIGHT : LEFT)) : LEFT_FALLING;
			RIGHT:
				next_state = ground ? (dig ? RIGHT_DIGGING : (bump_right ? LEFT : RIGHT)) : RIGHT_FALLING;
			LEFT_FALLING:
				next_state = ground ? LEFT : LEFT_FALLING;
			RIGHT_FALLING:
				next_state = ground ? RIGHT : RIGHT_FALLING;
			LEFT_DIGGING:
				next_state = ground ? LEFT_DIGGING : LEFT_FALLING;
			RIGHT_DIGGING:
				next_state = ground ? RIGHT_DIGGING : RIGHT_FALLING;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		state <= areset ? LEFT : next_state;

	assign walk_left = state == LEFT;
	assign walk_right = state == RIGHT;
	assign aaah = (state == LEFT_FALLING) | (state == RIGHT_FALLING);
	assign digging = (state == LEFT_DIGGING) | (state == RIGHT_DIGGING);

endmodule
