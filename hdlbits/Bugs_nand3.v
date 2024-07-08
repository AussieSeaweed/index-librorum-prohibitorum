module top_module (
	input a,
	input b,
	input c,
	output out
);

	wire outn;

	andgate inst1(outn, a, b, c, 1'b1, 1'b1);

	assign out = ~outn;

endmodule
