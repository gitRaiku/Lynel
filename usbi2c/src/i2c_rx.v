`timescale 1ns / 1ps

module i2c_rx(
    input sys_clk, 
    input rst_n,
    inout wire sda,
    wire scl,
    output reg [7:0]frame,
    inout reg frameReady,
);

reg [1:0]cstate;
reg [5:0]stateq;

localparam START 6'b110100;
localparam STOP  6'b000111;

reg logicState; // 0 = Inactive comm 1 = Active comm

reg [2:0] bitc;
reg [7:0] cframe;

function updFrame ();
  if (bitc == 3'd8) begin
    sda <= 1'b0;
    if ((cstate != lstate) && (!scl)) begin
      sda <= 1'bz;
      bitc <= 3'd0;
      lframe <= cframe;
      frameReady <= 1'b1;
    end
  end else begin
    if ((cstate != lstate) && (scl)) begin
      cframe <= { cframe[6:0], sda };
      bitc <= bitc + 1;
    end
  end
endfunction

always @(posedge sys_clk) begin
  if (!rst_n) begin
    cstate <= 2'b00;
    stateq <= 6'h00;
    logicstate <= 1'b0;
  end else begin
  lstate <= cstate;
  cstate = { sda, scl };
  if (stateq[1:0] != cstate) begin
    stateq <= { stateq[3:0], cstate }
  end
  if (logicState == 1) begin
    if (stateq == STOP) begin
      logicState <= 0;
      bitc <= 3'b000;
    end else begin
      updFrame();
    end
  end else begin
    if (stateq == START) begin
      bitc <= 3'b000;
      logicState <= 1;
    end
  end
end

  
  
end
