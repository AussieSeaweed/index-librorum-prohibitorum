module top_module (
	input cpu_overheated,
	output reg shut_off_computer,
	input arrived,
	input gas_tank_empty,
	output reg keep_driving
);

	always @(*)
		shut_off_computer = cpu_overheated;

	always @(*)
		keep_driving = arrived ? 0 : ~gas_tank_empty;

endmodule
