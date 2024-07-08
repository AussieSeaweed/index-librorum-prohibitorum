module top_module (
	input clk,
	input x,
	output z
);

	reg q0, q1, q2;

	always @(posedge clk) begin
		q0 <= x ^ q0;
		q1 <= x & ~q1;
		q2 <= x | ~q2;
	end

	assign z = ~(q0 | q1 | q2);

endmodule
