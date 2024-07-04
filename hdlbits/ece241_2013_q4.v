module top_module (
	input clk,
	input reset,
	input [3:1] s,
	output reg fr3,
	output reg fr2,
	output reg fr1,
	output reg dfr
);

	parameter s3 = 3'd0, s2 = 3'd1, s2d = 3'd2, s1 = 3'd3, s1d = 3'd4, s0d = 3'd5;
	reg [2:0] state, next_state;

	always @(*)
		case (state)
			s3:
				next_state = s[3] ? s3 : s2d;
			s2, s2d:
				next_state = s[3] ? s3 : (s[2] ? state : s1d);
			s1, s1d:
				next_state = s[2] ? s2 : (s[1] ? state : s0d);
			s0d:
				next_state = s[1] ? s1 : state;
			default:
				$fatal;
		endcase

	always @(posedge clk)
		state <= reset ? s0d : next_state;

	always @(*) begin
		case (state)
			s3:
				{fr3, fr2, fr1} = 3'b000;
			s2, s2d:
				{fr3, fr2, fr1} = 3'b001;
			s1, s1d:
				{fr3, fr2, fr1} = 3'b011;
			s0d:
				{fr3, fr2, fr1} = 3'b111;
			default:
				$fatal;
		endcase

		case (state)
			s3, s2, s1:
				dfr = 1'b0;
			s2d, s1d, s0d:
				dfr = 1'b1;
			default:
				$fatal;
		endcase
	end

endmodule
