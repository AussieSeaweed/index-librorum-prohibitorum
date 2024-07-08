module top_module (clk, reset, in, out);
	input clk;
	input reset;
	input in;
	output out;
	reg out;

	parameter A = 1'b0, B = 1'b1;

	reg present_state, next_state;

	always @(posedge clk)
		if (reset) begin
			present_state = B;
			out = 1'b1;
		end else begin
			case (present_state)
				A:
					next_state = in ? A : B;
				B:
					next_state = in ? B : A;
				default:
					$fatal;
			endcase

			present_state = next_state;

			case (present_state)
				A:
					out = 1'b0;
				B:
					out = 1'b1;
				default:
					$fatal;
			endcase
		end

endmodule
