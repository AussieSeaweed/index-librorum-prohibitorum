module top_module (
	input clk,
	input reset,
	input data,
	output reg [3:0] count,
	output reg counting,
	output reg done,
	input ack
);

	parameter S = 4'b0000;
	parameter S1 = 4'b0001;
	parameter S11 = 4'b0010;
	parameter S110 = 4'b0011;
	parameter S1101_O0 = 4'b0100;
	parameter O1 = 4'b0101;
	parameter O2 = 4'b0110;
	parameter O3 = 4'b0111;
	parameter O4_C = 4'b1000;
	parameter D = 4'b1001;

	reg shift_ena, done_counting;
	reg [3:0] state, next_state;
	reg [13:0] delay, next_delay;

	always @(*) begin
		case (state)
			S:
				next_state = data ? S1 : S;
			S1:
				next_state = data ? S11 : S;
			S11:
				next_state = data ? S11 : S110;
			S110:
				next_state = data ? S1101_O0 : S;
			S1101_O0:
				next_state = O1;
			O1:
				next_state = O2;
			O2:
				next_state = O3;
			O3:
				next_state = O4_C;
			O4_C:
				next_state = done_counting ? D : O4_C;
			D:
				next_state = ack ? S : D;
			default:
				$fatal;
		endcase

		case (state)
			S1101_O0:
				next_delay = {data, 13'b1111111111111};
			O1:
				next_delay = {delay[13], data, 12'b111111111111};
			O2:
				next_delay = {delay[13:12], data, 11'b11111111111};
			O3:
				next_delay = {delay[13:11], data, 10'd999};
			O4_C:
				next_delay = |delay[9:0] ? {delay[13:10], delay[9:0] - 10'b1} : {delay[13:10] - 4'b1, 10'd999};
			default:
				next_delay = delay;
		endcase
	end

	always @(posedge clk) begin
		state <= reset ? S : next_state;
		delay <= reset ? 14'b11111111111111 : next_delay;
	end

	always @(*) begin
		count = delay[13:10];
		counting = state == O4_C;
		done = state == D;

		case (state)
			S1101_O0, O1, O2, O3:
				shift_ena = 1'b1;
			default:
				shift_ena = 1'b0;
		endcase

		done_counting = ~|delay;
	end

endmodule
