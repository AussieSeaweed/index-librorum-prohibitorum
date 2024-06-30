module top_module (
	input [3:0] in,
	output reg [1:0] pos
);

	always @(*)
		case (in)
			4'b0000, 4'b0001, 4'b0011, 4'b0101, 4'b0111, 4'b1001, 4'b1011, 4'b1101, 4'b1111:
				pos = 2'd0;
			4'b0010, 4'b0110, 4'b1010, 4'b1110:
				pos = 2'd1;
			4'b0100, 4'b1100:
				pos = 2'd2;
			4'b1000:
				pos = 2'd3;
			default:
				pos = 2'd3;
		endcase

endmodule
