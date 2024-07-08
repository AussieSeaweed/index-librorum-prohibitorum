module top_module (
	input clk,
	input in,
	input reset,
	output reg [7:0] out_byte,
	output done
);

	parameter INACTIVE = 7'b0000000, ACTIVE = 7'b01zzzzz, ACTIVE_ZERO = 7'b0100000, ACTIVE_EIGHT = 7'b01z1000, ACTIVE_NINE = 7'b01z1001, SUCCESS = 7'b1000000, FAILURE = 7'b1000001;
	reg [6:0] state, next_state;

	always @(*)
		casez (state)
			INACTIVE, SUCCESS:
				next_state = in ? INACTIVE : ACTIVE_ZERO;
			ACTIVE_EIGHT:
				next_state = state[4] ^ in ? ACTIVE_NINE : FAILURE;
			ACTIVE_NINE:
				next_state = in ? SUCCESS : FAILURE;
			ACTIVE:
				next_state = (state + 7'b1) ^ {2'b00, in, 4'b0000};
			FAILURE:
				next_state = in ? INACTIVE : FAILURE;
			default:
				$fatal;
		endcase

	always @(posedge clk) begin
		if (((state & ACTIVE_ZERO) == ACTIVE_ZERO) & ((state & 7'b1111) < 8))
			out_byte[state & 7'b1111] <= in;

		state <= reset ? INACTIVE : next_state;
	end

	assign done = state == SUCCESS;

endmodule
