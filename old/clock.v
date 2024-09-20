module cligger12 (
  input clk50, input rst_n,
  output wire clk12);

reg[4:0] div;
reg out;

assign clk12 = out;

always @(posedge clk50) begin
  if (!rst_n) begin
    div <= 5'b00000;
    out <= 1'b0;
  end else begin
    case (div) /// Yandere sim sim
      0 : out <= 1'b1;
      2 : out <= 1'b0;
      4 : out <= 1'b1;
      6 : out <= 1'b0;
      8 : out <= 1'b1;
      10: out <= 1'b0;
      12: out <= 1'b1;
      15: out <= 1'b0;
      17: out <= 1'b1;
      19: out <= 1'b0;
      21: out <= 1'b1;
      23: out <= 1'b0;
    endcase
    if (div == 25) begin
      div <= 5'b00000;
    end else begin
      div <= div + 1'b1;
    end
  end
end

endmodule
