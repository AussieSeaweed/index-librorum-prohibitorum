module top_module (
	input clk,
	input reset,
	output shift_ena
);

	parameter O0 = 3'b000;
	parameter O1 = 3'b001;
	parameter O2 = 3'b010;
	parameter O3 = 3'b011;
	parameter O4 = 3'b100;

	reg [2:0] state, next_state;

	always @(*)
		case (state)
			O0:
				next_state = O1;
			O1:
				next_state = O2;
			O2:
				next_state = O3;
			O3:
				next_state = O4;
			O4:
				next_state = O4;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? O0 : next_state;

	assign shift_ena = state != O4;

endmodule
