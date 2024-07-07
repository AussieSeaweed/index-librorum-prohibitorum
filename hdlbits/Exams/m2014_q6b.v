module top_module (
	input [3:1] y,
	input w,
	output Y2
);

	parameter B = 3'b001;
	parameter C = 3'b010;
	parameter E = 3'b100;
	parameter F = 3'b101;

	assign Y2 = (y == B) | (y == F) | w & ((y == C) | (y == E));

endmodule
