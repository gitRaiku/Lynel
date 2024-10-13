`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    output wire led_1,
    output wire led_2,
    inout wire sda,
    input wire scl);

reg l1, l2; 
assign led_1 = l1;
assign led_2 = l2;

localparam FRAMECOUNT = 6;

wire doneframe;
// wire [0:7]frames[0:FRAMECOUNT - 1];

i2c_slave #(.FRAMECOUNT(FRAMECOUNT)) slave (
    .sys_clk(sys_clk),
    .rst_n(rst_n),
    .sda(sda), 
    .scl(scl));
    
always @(posedge doneframe) begin
  l1 <= 1;
end

always @(negedge doneframe) begin
  l1 <= 0;
end


always @(posedge sys_clk) begin
  if (!rst_n) begin
    l1 <= button_1;
    l2 <= 0;
  end else begin
    l2 <= scl;
  end
end

endmodule

