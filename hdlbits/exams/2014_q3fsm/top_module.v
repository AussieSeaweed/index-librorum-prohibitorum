module top_module (
	input clk,
	input reset,
	input s,
	input w,
	output z
);

	parameter A = 5'b00000;
	parameter B0X = 5'b10000;
	parameter B02 = 5'b10010;
	parameter B10 = 5'b10100;
	parameter B11 = 5'b10101;
	parameter B20 = 5'b11000;
	parameter B21 = 5'b11001;
	parameter B22 = 5'b11010;
	reg [4:0] state, next_state;

	always @(*)
		case (state)
			A:
				next_state = s ? B0X : A;
			B0X, B02:
				next_state = w ? B11 : B10;
			B10:
				next_state = w ? B21 : B20;
			B11:
				next_state = w ? B22 : B21;
			B20:
				next_state = B0X;
			B21:
				next_state = w ? B02 : B0X;
			B22:
				next_state = w ? B0X : B02;
		endcase

	always @(posedge clk)
		state <= reset ? A : next_state;

	assign z = state == B02;

endmodule
