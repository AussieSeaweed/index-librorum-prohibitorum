module top_module(
	input clk,
	input [7:0] in,
	input reset,
	output [23:0] out_bytes,
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

	always @(posedge clk) begin
		case (state)
			ZERO, THREE:
				out_bytes[23:16] <= in;
			ONE:
				out_bytes[15:8] <= in;
			TWO:
				out_bytes[7:0] <= in;
			default:
				$fatal;
		endcase

		state <= reset ? ZERO : next_state;
	end

	assign done = state == THREE;

endmodule
