module top_module (
	input clk,
	input areset,
	input load,
	input ena,
	input [3:0] data,
	output reg [3:0] q
); 

	always @(posedge clk, posedge areset)
		if (areset)
			q <= 4'h0;
		else if (load)
			q <= data;
		else if (ena)
			q <= q >> 1;

endmodule
