module top_module (
	input clk,
	input areset,
	input x,
	output z
);

	parameter A = 1'b0, B = 1'b1;
	reg state, next_state;

	always @(*)
		case (state)
			A:
				next_state = x ? B : A;
			B:
				next_state = B;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		state <= areset ? A : next_state;

	assign z = (state == B) ^ x;

endmodule
