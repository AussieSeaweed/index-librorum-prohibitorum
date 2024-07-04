module top_module(
	input clk,
	input reset,
	input j,
	input k,
	output out
);

	parameter OFF = 1'b0, ON = 1'b1;
	reg state, next_state;

	always @(*)
		case (state)
			OFF:
				next_state = j ? ON : OFF;
			ON:
				next_state = k ? OFF : ON;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? OFF : next_state;

	assign out = state;

endmodule
