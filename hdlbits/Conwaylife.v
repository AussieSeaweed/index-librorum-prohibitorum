module top_module (
	input clk,
	input load,
	input [255:0] data,
	output [255:0] q
);
	genvar i;

	generate
		for (i = 0; i < 256; i = i + 1) begin : gaming
			localparam r = i / 16;
			localparam c = i % 16;
			localparam pr = (r - 1 + 16) % 16;
			localparam nr = (r + 1) % 16;
			localparam pc = (c - 1 + 16) % 16;
			localparam nc = (c + 1) % 16;

			game gi(
				clk,
				load,
				{
					q[pr * 16 + pc],
					q[pr * 16 + c],
					q[pr * 16 + nc],
					q[r * 16 + pc],
					q[r * 16 + nc],
					q[nr * 16 + pc],
					q[nr * 16 + c],
					q[nr * 16 + nc],
				},
				data[i],
				q[i]
			);
		end
	endgenerate

endmodule

module game (
	input clk,
	input reset,
	input [7:0] neighbors,
	input d,
	output reg q
);

	wire [2:0] neighbor_count;

	popcount pc(neighbors, neighbor_count);

	always @(posedge clk)
		if (reset)
			q <= d;
		else
			case (neighbor_count)
				3'd0, 3'd1, 3'd4, 3'd5, 3'd6, 3'd7, 3'd8:
					q <= 1'b0;
				3'd2:
					$pass;
				3'd3:
					q <= 1'b1;
				default:
					$fatal;
			endcase

endmodule

module popcount (
	input [7:0] in,
	output reg [2:0] out
);

	always @(*) begin
		out = 0;

		for (integer i = 0; i < 8; ++i)
			out += in[i];
	end

endmodule
