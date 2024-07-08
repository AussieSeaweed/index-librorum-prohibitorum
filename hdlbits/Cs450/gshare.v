module top_module (
	input clk,
	input areset,

	input  predict_valid,
	input  [6:0] predict_pc,
	output reg predict_taken,
	output reg [6:0] predict_history,

	input train_valid,
	input train_taken,
	input train_mispredicted,
	input [6:0] train_history,
	input [6:0] train_pc
);

	reg [255:0] pht, npht;

	parameter SNT = 2'b00, WNT = 2'b01, WT = 2'b10, ST = 2'b11;

	always @(*) begin
		npht = pht;

		if (train_valid)
			case (pht[{train_history ^ train_pc, 1'b0}+:2])
				SNT:
					npht[{train_history ^ train_pc, 1'b0}+:2] = train_taken ? WNT : SNT;
				WNT:
					npht[{train_history ^ train_pc, 1'b0}+:2] = train_taken ? WT : SNT;
				WT:
					npht[{train_history ^ train_pc, 1'b0}+:2] = train_taken ? ST : WNT;
				ST:
					npht[{train_history ^ train_pc, 1'b0}+:2] = train_taken ? ST : WT;
				default:
					$fatal;
			endcase
	end
	
	always @(posedge clk, posedge areset)
		pht <= areset ? {128{WNT}} : npht;

	reg [6:0] next_predict_history;

	always @(*)
		case (pht[{predict_pc ^ predict_history, 1'b0}+:2])
			SNT, WNT:
				predict_taken = 1'b0;
			WT, ST:
				predict_taken = 1'b1;
			default:
				$fatal;
		endcase

	always @(posedge clk, posedge areset)
		if (areset)
			predict_history <= 7'd0;
		else if (train_valid & train_mispredicted)
			predict_history <= {train_history[5:0], train_taken};
		else if (predict_valid)
			predict_history <= {predict_history[5:0], predict_taken};

endmodule
