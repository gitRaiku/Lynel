`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    output wire led_1,
    output wire led_2,
    inout wire sda,
    input wire scl);

reg cb; 
assign led_1 = cb;
assign led_2 = cb;

wire [7:0]wframe;
reg cframenr;
wire framenr;

localparam FRAMECOUNT = 6;

wire doneframe;
wire [0:7]frames[0:FRAMECOUNT - 1];

i2c_slave slave #(parameter FRAMECOUNT=FRAMECOUNT) (
    .sys_clk(sys_clk),
    .rst_n(rst_n),
    .sda(sda), 
    .scl(scl),
    .sdoneframe(doneframe),
    .sframes(frames));
    
always @(posedge doneframe) begin

end


always @(posedge sys_clk) begin
  if (!rst_n) begin
  end else begin
  end
end

endmodule

