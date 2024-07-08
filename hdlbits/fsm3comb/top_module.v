module top_module (
	input in,
	input [1:0] state,
	output reg [1:0] next_state,
	output reg out
);

	parameter A = 2'd0, B = 2'd1, C = 2'd2, D = 2'd3;

	always @(*)
		case (state)
			A: begin
				next_state = in ? B : A;
				out = 1'b0;
			end
			B: begin
				next_state = in ? B : C;
				out = 1'b0;
			end
			C: begin
				next_state = in ? D : A;
				out = 1'b0;
			end
			D: begin
				next_state = in ? B : C;
				out = 1'b1;
			end
			default:
				$fatal;
		endcase

endmodule
