module top_module (
	input clk,
	input resetn,
	input x,
	input y,
	output f,
	output g
);

	parameter F0 = 4'b0000;
	parameter F1 = 4'b0001;
	parameter M = 4'b0010;
	parameter M1 = 4'b0011;
	parameter M10 = 4'b0100;
	parameter G = 4'b0101;
	parameter GG = 4'b0110;
	parameter G1 = 4'b0111;
	parameter G0 = 4'b1000;

	reg [3:0] state, next_state;

	always @(*)
		case (state)
			F0:
				next_state = F1;
			F1:
				next_state = M;
			M:
				next_state = x ? M1 : M;
			M1:
				next_state = x ? M1 : M10;
			M10:
				next_state = x ? G : M;
			G:
				next_state = y ? G1 : GG;
			GG:
				next_state = y ? G1 : G0;
			G1:
				next_state = G1;
			G0:
				next_state = G0;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= resetn ? next_state : F0;

	assign f = state == F1;
	assign g = (state == G) | (state == GG) | (state == G1);

endmodule
