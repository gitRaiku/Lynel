module usb_mod(
  input clk,
  input rst_n,
  inout dp,
  inout dm
);

/*
localparam
    st_idle = 3'b000,
    st_sync = 3'b101,
    st_run  = 3'b001,
    st_eop1 = 3'b010,
    st_eop2 = 3'b011,
    st_eop3 = 3'b100,
    st_crc1 = 3'b110,
    st_crc2 = 3'b111;
*/

reg dataparity;
reg cstate;
reg[3:0] bitstuf;



wire 

endmodule
