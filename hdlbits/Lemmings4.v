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

	parameter LEFT = 9'b000000000;
	parameter RIGHT = 9'b000100000;
	parameter LEFT_FALLING = 9'b0010zzzzz;
	parameter RIGHT_FALLING = 9'b0011zzzzz;
	parameter LEFT_FALLING_ZERO = 9'b001000000;
	parameter RIGHT_FALLING_ZERO = 9'b001100000;
	parameter LEFT_DIGGING = 9'b010000000;
	parameter RIGHT_DIGGING = 9'b010100000;
	parameter OOPS = 9'b0100000000;
	reg [9:0] state, next_state;

	always @(*)
		casez (state)
			LEFT:
				next_state = ground ? (dig ? LEFT_DIGGING : (bump_left ? RIGHT : LEFT)) : LEFT_FALLING_ZERO;
			RIGHT:
				next_state = ground ? (dig ? RIGHT_DIGGING : (bump_right ? LEFT : RIGHT)) : RIGHT_FALLING_ZERO;
			LEFT_FALLING:
				next_state = (state & 9'b11111) == 9'd20 ? (ground ? OOPS : state) : (ground ? LEFT : state + 9'b1);
			RIGHT_FALLING:
				next_state = (state & 9'b11111) == 9'd20 ? (ground ? OOPS : state) : (ground ? RIGHT : state + 9'b1);
			LEFT_DIGGING:
				next_state = ground ? LEFT_DIGGING : LEFT_FALLING_ZERO;
			RIGHT_DIGGING:
				next_state = ground ? RIGHT_DIGGING : RIGHT_FALLING_ZERO;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		state <= areset ? LEFT : next_state;

	assign walk_left = state == LEFT;
	assign walk_right = state == RIGHT;
	assign aaah = ((state & 9'b111100000) == LEFT_FALLING_ZERO) | ((state & 9'b111100000) == RIGHT_FALLING_ZERO);
	assign digging = (state == LEFT_DIGGING) | (state == RIGHT_DIGGING);

endmodule
