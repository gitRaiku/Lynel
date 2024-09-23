`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    output wire led_1,
    output wire led_2,
    inout wire sda,
    input wire scl,
    output wire [7:0]outframe
  );

reg [7:0]oframe;
assign outframe = oframe;
i2c_rx rx(sys_clk, rst_n, sda, scl);

always @(posedge sys_clk) begin
  if (!rst_n) begin  
  end else begin
    if (rx.frameReady) begin
      oframe = rx.frame;
      rx.frameReady = 'b0;
    end
  end
end

endmodule

