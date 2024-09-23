`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    inout wire sda,
    input wire scl,
    output wire led_1,
    output wire led_2);

wire [7:0]frame;
reg frameReady;

i2c_rx rx(sys_clk, rst_n, sda, scl, frame, frameReady);

always @(posedge sys_clk) begin
  if (!rst_n) begin
    fframeReady <= 1'b0;
  end else begin
  end
end

endmodule

