`timescale 1ns / 1ps

module testbench();

reg clk, rst_n;
wire sdaw, sclw;
reg sda, sda_write, scl;
assign sclw = scl;
assign sdaw = sda_write ? sda : 1'bz;
reg true;
wire [7:0]outframe;

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
    rst_n = 0; #20;
    rst_n = 1;
end

main mn(
    .sys_clk(clk),
    .rst_n(rst_n),
    .button_1(true),
    .led_1(),
    .led_2(),
    .sda(sdaw),
    .scl(sclw),
    .outframe(outframe));

initial begin
    #40;
    sda_write = 1;
    sda = 0; #15;
    scl = 0; #15;
    
    scl = 0; #15;
    sda = 1; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 0; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 1; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 0; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 1; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 0; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 1; #5; scl = 1; #15; scl = 0; #5 sda = 0; #15;
    sda = 0; #5; scl = 1; #15; scl = 0; #5 sda_write = 0; #15;
    #5; scl = 1; #15; scl = 0; #15; sda = 1'b1; sda_write = 1;
    
    $finish;
end


    
endmodule
