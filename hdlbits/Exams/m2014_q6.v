module top_module (
	input clk,
	input reset,
	input w,
	output reg z
);

	parameter A = 3'b000;
	parameter B = 3'b001;
	parameter C = 3'b010;
	parameter D = 3'b011;
	parameter E = 3'b100;
	parameter F = 3'b101;

	reg [2:0] state, next_state;

	always @(*)
		case (state)
			A:
				next_state = w ? A : B;
			B:
				next_state = w ? D : C;
			C:
				next_state = w ? D : E;
			D:
				next_state = w ? A : F;
			E:
				next_state = w ? D : E;
			F:
				next_state = w ? D : C;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state = reset ? A : next_state;

	always @(*)
		case (state)
			A, B, C, D:
				z = 1'b0;
			E, F:
				z = 1'b1;
			default:
				$fatal;
		endcase

endmodule
