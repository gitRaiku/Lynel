`timescale 1ns / 1ps

module cdc #(parameter BITC=1) (
    input sys_clk, input rst_n, 
    input [0:BITC-1]in,
    output reg [0:BITC-1]out);

    reg [0:BITC-1]ivar[0:1];

    always @(posedge sys_clk) begin
      if (!rst_n) begin
        ivar[0] <= {BITC{1'b0}};
        ivar[1] <= {BITC{1'b0}};
      end else begin
        out <= ivar[1];
        ivar[1] <= ivar[0];
        ivar[0] <= in;
      end
    end
endmodule

module cdcv #(parameter BITC=1, VLEN=1) (
    input sys_clk, input rst_n, 
    input [0:BITC-1]in[0:VLEN-1],
    output reg [0:BITC-1]out[0:VLEN-1]);

    reg [0:BITC-1]ivar[0:VLEN-1][0:1];

    always @(posedge sys_clk) begin
      integer i;
      if (!rst_n) begin
        for (i = 0; i < VLEN; i = i + 1) begin
          ivar[i][0] <= {BITC{1'b0}};
          ivar[i][1] <= {BITC{1'b0}};
        end
      end else begin
        for (i = 0; i < VLEN; i = i + 1) begin
          out[i] <= ivar[i][1];
          ivar[i][1] <= ivar[i][0];
          ivar[i][0] <= in[i];
        end
      end
    end
endmodule
