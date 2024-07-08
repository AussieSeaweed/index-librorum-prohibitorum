module top_module (
	input clk,
	input resetn,
	input [3:1] r,
	output [3:1] g
);

	parameter A = 2'b00, B = 2'b01, C = 2'b10, D = 2'b11;

	reg [1:0] state, next_state;

	always @(*)
		case (state)
			A:
				next_state = r[1] ? B : (r[2] ? C : (r[3] ? D : A));
			B:
				next_state = r[1] ? B : A;
			C:
				next_state = r[2] ? C : A;
			D:
				next_state = r[3] ? D : A;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= resetn ? next_state : A;

	assign g = {state == D, state == C, state == B};

endmodule
