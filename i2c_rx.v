`timescale 1ns / 1ps

module i2c_rx

#(parameter [6:0]ADDR=7'b0000000,
  parameter SNIFF=0'b0) (
  input sys_clk,
  input rst_n,
  input read_enabled,
  wire i2c_scl,
  inout i2c_sda
);

reg cstate;

reg [8:0]frame;
reg [4:0]cbit;

reg ack = 0;
assign i2c_sda = (SNIFF == 0'b0 && ack) ? 1'b1 : 'bz;

always @(posedge sys_clk) begin
  if (!rst_n) begin
    cbuf <= 8'h0000;
    cstate <= 1'b0;
    cbit <= 4'b0000;
    ack <= 0;
  end else begin
    if (i2c_scl != cstate) begin
      cstate <= i2c_scl;
      if (i2c_scl) begin
        if (SNIFF) begin
          frame <= { [7:0]frame, i2c_sda };
          cbit <= cbit + 1;
        end else begin
          if (cbit == 5'h9) begin
            end else if (cbit == 5'h8) begin
            ack <= 1; cbit <= cbit + 1;
          end else if (cbit == 5'h8) begin
            cbit <= 0;
          end else begin
            cbit <= cbit + 1;
          end
        end
      end else begin
        if (cbit == 5'b10000) begin
          ack <= 1;
        end
        if (cbit == 5'b10000) begin
          ack <= 1;
        end
      end
    end
  end
endmodule
