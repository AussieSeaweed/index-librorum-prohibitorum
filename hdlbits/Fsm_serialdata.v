module top_module (
	input clk,
	input in,
	input reset,
	output reg [7:0] out_byte,
	output done
);

	parameter INACTIVE = 6'b000000, ACTIVE = 6'b01zzzz, ACTIVE_ZERO = 6'b010000, ACTIVE_EIGHT = 6'b011000, SUCCESS = 6'b100000, FAILURE = 6'b100001;
	reg [5:0] state, next_state;

	always @(*)
		casez (state)
			INACTIVE, SUCCESS:
				next_state = in ? INACTIVE : ACTIVE_ZERO;
			ACTIVE_EIGHT:
				next_state = in ? SUCCESS : FAILURE;
			ACTIVE:
				next_state = state + 4'b1;
			FAILURE:
				next_state = in ? INACTIVE : FAILURE;
			default:
				$fatal;
		endcase

	always @(posedge clk) begin
		if (((state & ACTIVE_ZERO) == ACTIVE_ZERO) & (state != ACTIVE_EIGHT))
			out_byte[state - ACTIVE_ZERO] = in;

		state <= reset ? INACTIVE : next_state;
	end

	assign done = state == SUCCESS;

endmodule
