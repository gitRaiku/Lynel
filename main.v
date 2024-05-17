`timescale 1ns / 1ps

`include "usb.v"

module (
  input sys_clk,
  input rst_n,
  input usb_dplus,
  input usb_dminus
);

usb_mod(
  sys_clk, rst_n,
  usb_dplus, usb_dminus
) ;

endmodule
