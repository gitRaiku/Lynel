`timescale 1ns / 1ps

module testbench();

reg clk, rst_n;
wire sdaw, sclw;
reg sda, sda_write, scl;
assign sclw = scl;
assign sdaw = sda_write ? sda : 1'bz;
reg true;
integer i, j;

always begin
    clk = 1; #5;
    clk = 0; #5;
end

initial begin
    sda = 1'b1;
    sda_write = 1'b0;
    true = 1;
    sda = 1;
    scl = 1;
    rst_n = 0; #10;
    sda_write <= 1'b1; sda = 1; #10;
    rst_n = 1; 
end

main mn(
    .sys_clk(clk),
    .rst_n(rst_n),
    .button_1(true),
    .led_1(),
    .led_2(),
    .sda(sdaw),
    .scl(sclw));

reg [0:7]snda[0:5];

initial begin
    #40;
    snda[0] <= 8'b00110100;
    snda[1] <= 8'b10000010;
    snda[2] <= 8'b01000101;
    snda[3] <= 8'b00101000;
    snda[4] <= 8'b00010000;
    snda[5] <= 8'b00000000;
    sda_write = 1;
    sda = 0; #15;
    scl = 0; #15;
    
    for (i = 0; i < 5; i = i + 1) begin
      for (j = 0; j < 8; j = j + 1) begin
        sda = snda[i][j]; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
      end
      sda_write = 0; #5; scl = 1; #15; scl = 0; #8; sda = 0; sda_write = 1; 
    end
    scl = 1; #15;
    sda = 1; #15;

    sda_write = 0;
    
    $finish;
end


    
endmodule
