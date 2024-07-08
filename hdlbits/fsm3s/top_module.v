module top_module (
	input clk,
	input in,
	input reset,
	output reg out
);

	parameter A = 2'd0, B = 2'd1, C = 2'd2, D = 2'd3;

	reg [1:0] state, next_state;

	always @(*)
		case (state)
			A:
				next_state <= in ? B : A;
			B:
				next_state <= in ? B : C;
			C:
				next_state <= in ? D : A;
			D:
				next_state <= in ? B : C;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? A : next_state;

	always @(*)
		case (state)
			A, B, C:
				out = 1'b0;
			D:
				out = 1'b1;
			default:
				$fatal;
		endcase

endmodule
