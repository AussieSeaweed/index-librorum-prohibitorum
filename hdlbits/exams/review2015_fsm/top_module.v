module top_module (
	input clk,
	input reset,
	input data,
	output reg shift_ena,
	output reg counting,
	input done_counting,
	output reg done,
	input ack
);

	parameter S = 4'b0000;
	parameter S1 = 4'b0001;
	parameter S11 = 4'b0010;
	parameter S110 = 4'b0011;
	parameter S1101_O0 = 4'b0100;
	parameter O1 = 4'b0101;
	parameter O2 = 4'b0110;
	parameter O3 = 4'b0111;
	parameter O4_C = 4'b1000;
	parameter D = 4'b1001;

	reg [3:0] state, next_state;

	always @(*)
		case (state)
			S:
				next_state = data ? S1 : S;
			S1:
				next_state = data ? S11 : S;
			S11:
				next_state = data ? S11 : S110;
			S110:
				next_state = data ? S1101_O0 : S;
			S1101_O0:
				next_state = O1;
			O1:
				next_state = O2;
			O2:
				next_state = O3;
			O3:
				next_state = O4_C;
			O4_C:
				next_state = done_counting ? D : O4_C;
			D:
				next_state = ack ? S : D;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? S : next_state;

	always @(*) begin
		case (state)
			S1101_O0, O1, O2, O3:
				shift_ena = 1'b1;
			default:
				shift_ena = 1'b0;
		endcase

		counting = state == O4_C;
		done = state == D;
	end

endmodule
