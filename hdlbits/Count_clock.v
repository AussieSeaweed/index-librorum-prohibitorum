module top_module (
	input clk,
	input reset,
	input ena,
	output pm,
	output [7:0] hh,
	output [7:0] mm,
	output [7:0] ss
);

	wire [3:0] ampmq;

	assign pm = ampmq[0];

	wire s0end, s1end, m0end, m1end, h0end, h1end, ampmend;

	assign s0end = ss[3:0] == 4'h9;
	assign s1end = ss[7:4] == 4'h5;
	assign m0end = mm[3:0] == 4'h9;
	assign m1end = mm[7:4] == 4'h5;
	assign h0end = h1end ? hh[3:0] == 4'h2 : hh[3:0] == 4'h9;
	assign h1end = hh[7:4] == 4'h1;
	assign ampmend = ampmq[3:0] == 4'h1;

	wire s0ena, s1ena, m0ena, m1ena, h0ena, h1ena, ampmena;

	assign s0ena = ena;
	assign s1ena = s0end & s0ena;
	assign m0ena = s1end & s1ena;
	assign m1ena = m0end & m0ena;
	assign h0ena = m1end & m1ena;
	assign h1ena = h0end & h0ena;
	assign ampmena = (hh == 8'h11) & h0ena;

	wire s0reset, s1reset, m0reset, m1reset, h0reset, h1reset, ampmreset;

	assign s0reset = reset | (s0end & s0ena);
	assign s1reset = reset | (s1end & s1ena);
	assign m0reset = reset | (m0end & m0ena);
	assign m1reset = reset | (m1end & m1ena);
	assign h0reset = reset | (h0end & h0ena);
	assign h1reset = reset | (h1end & h1ena);
	assign ampmreset = reset | (ampmend & ampmena);

	wire [3:0] s0d, s1d, m0d, m1d, h0d, h1d, ampmd;

	assign s0d = 4'h0;
	assign s1d = 4'h0;
	assign m0d = 4'h0;
	assign m1d = 4'h0;
	assign h0d = reset ? 4'h2 : (h1end ? 4'h1 : 4'h0);
	assign h1d = reset ? 4'h1 : 4'h0;
	assign ampmd = 4'h0;

	counter s0(clk, s0reset, s0ena, s0d, ss[3:0]);
	counter s1(clk, s1reset, s1ena, s1d, ss[7:4]);
	counter m0(clk, m0reset, m0ena, m0d, mm[3:0]);
	counter m1(clk, m1reset, m1ena, m1d, mm[7:4]);
	counter h0(clk, h0reset, h0ena, h0d, hh[3:0]);
	counter h1(clk, h1reset, h1ena, h1d, hh[7:4]);
	counter ampm(clk, ampmreset, ampmena, ampmd, ampmq);

endmodule

module counter (
	input clk,
	input reset,
	input ena,
	input [3:0] d,
	output reg [3:0] q
);

	always @(posedge clk)
		if (ena | reset)
			q <= reset ? d : q + 4'h1;

endmodule
