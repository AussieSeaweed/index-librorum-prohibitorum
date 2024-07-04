module top_module(
	input clk,
	input [7:0] in,
	input reset,
	output done
);

	parameter ZERO = 2'd0, ONE = 2'd1, TWO = 2'd2, THREE = 2'd3;
	reg [1:0] state, next_state;

	always @(*)
		case (state)
			ZERO:
				next_state = in[3] ? ONE : ZERO;
			ONE:
				next_state = TWO;
			TWO:
				next_state = THREE;
			THREE:
				next_state = in[3] ? ONE : ZERO;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? ZERO : next_state;

	assign done = state == THREE;

endmodule
