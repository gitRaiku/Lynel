module cligger12 (
  input clk50, input rst_n,
  output reg clk12);

reg[4:0] div;

always @(posedge clk50) begin
  if (!rst_n) begin
    div <= 5'b00000;
  end else begin
    case (div) /// Yandere sim sim
      0 : clk12 <= 1'b1;
      2 : clk12 <= 1'b0;
      4 : clk12 <= 1'b1;
      6 : clk12 <= 1'b0;
      8 : clk12 <= 1'b1;
      10: clk12 <= 1'b0;
      12: clk12 <= 1'b1;
      15: clk12 <= 1'b0;
      17: clk12 <= 1'b1;
      19: clk12 <= 1'b0;
      21: clk12 <= 1'b1;
      23: clk12 <= 1'b0;
    endcase
    if (div == 25) begin
      div <= 5'b00000;
    end else begin
      div <= div + 1'b1;
    end
  end
end

endmodule
