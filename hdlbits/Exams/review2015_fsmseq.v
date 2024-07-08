module top_module (
	input clk,
	input reset,
	input data,
	output start_shifting
);

	parameter S = 3'b000;
	parameter S1 = 3'b001;
	parameter S11 = 3'b010;
	parameter S110 = 3'b011;
	parameter S1101 = 3'b100;

	reg [2:0] state, next_state;

	always @(*)
		case (state)
			S:
				next_state = data ? S1 : S;
			S1:
				next_state = data ? S11 : S;
			S11:
				next_state = data ? S11 : S110;
			S110:
				next_state = data ? S1101 : S;
			S1101:
				next_state = S1101;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? S : next_state;

	assign start_shifting = state == S1101;

endmodule
