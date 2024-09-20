`timescale 1ns / 1ps

module i2c_reciever#(
  parameter [6:0]ADDR=7'h00,
  parameter SNIFF=1'b0) (
  input sys_clk, input rst_n,
  input read_enabled,
  wire i2c_scl, inout i2c_sda
);
  reg [8:0]lastFrame;
  reg frameReady;
  reg [3:0]cframe;
  i2c_rx #(SNIFF=SNIFF) reciever(sys_clk, rst_n, read_enabled, i2c_scl, i2c_sda, lastFrame, frameReady);

  always @(posedge sys_clk) begin
    if (!rst_n || !read_enabled) begin 
      cframe <= 4'h0;
    end else begin 
      if (frameReady) begin
        frameReady <= 1'b0;

      end
    end
  end
endmodule

module i2c_rx
#(parameter SNIFF=1'b0) (
  input sys_clk, input rst_n,
  input read_enabled,
  wire i2c_scl, inout i2c_sda,
  output [8:0]lastFrame,
  output frameReady
);

/// TODO: Figure out how to detect START/STOP's? like what if error and whole shebang go fucky wucky?

reg cstate;

reg [8:0]frame;
reg [4:0]cbit;

reg ack = 0;
assign i2c_sda = (SNIFF == 0'b0 && ack) ? 1'b1 : 'bz;

always @(posedge sys_clk) begin
  if (!rst_n || !read_enabled) begin
    cbuf <= 8'h0;
    cstate <= 1'h0;
    cbit <= 4'h0;
    ack <= 1'h0;
    lastFrame <= 8'h0;
    frameReady <= 1'h0;
  end else begin
    if (i2c_scl != cstate) begin
      cstate <= i2c_scl;
      if (SNIFF) begin
        if (i2c_scl) begin
          frame <= { [7:0]frame, i2c_sda };
          if (cbit == 5'h9) begin
            cbit <= 1'h0;
            lastFrame <= frame;
            frameReady <= 1'h1;
          end else cbit <= cbit + 1'h1;
        end
      end else if (i2c_scl) begin
        frame <= { [7:0]frame, i2c_sda };
        cbit <= cbit + 1'h1;
        if (cbit == 5'h8) begin
          ack <= 1'h1;
        end
      end else begin
        if (cbit == 5'h9) begin
          lastFrame <= frame;
          frameReady <= 1'h1;
          ack <= 1'h0;
          cbit <= 1'h0;
        end
      end
    end
  end
endmodule
