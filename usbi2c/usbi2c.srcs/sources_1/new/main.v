`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    output wire led_1,
    output wire led_2,
    inout wire sda,
    input wire scl,
    output reg [7:0]outframe
  );

reg cb; 
assign led_1 = cb;
assign led_2 = cb;

wire [7:0]wframe;
reg cframenr;
wire framenr;

i2c_rx rx(
    .sys_clk(sys_clk), 
    .rst_n(rst_n), 
    .sda(sda), 
    .scl(scl),
    .frame(wframe),
    .framenr(framenr)
    );


always @(posedge sys_clk) begin
  if (!rst_n) begin
    cb <= 1'b0;
    cframenr <= 1'b1;  
    outframe <= 8'h00;
  end else begin
    if (cframenr == framenr) begin
      outframe <= wframe;
      cframenr <= cframenr + 1;
    end
    cb <= button_1;
  end
end

endmodule

