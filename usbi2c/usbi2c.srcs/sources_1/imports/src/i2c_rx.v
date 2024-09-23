`timescale 1ns / 1ps

module i2c_rx(
    input sys_clk, 
    input rst_n,
    inout wire sda,
    input wire scl
);

reg frameReady;
reg [7:0]frame;

reg sdapulldown;
assign sda = sdapulldown ? 1'bz : 1'b0;

reg [1:0]cstate;
reg [1:0]lstate;
reg [5:0]stateq;

localparam START = 6'b110100;
localparam STOP = 6'b000111;

reg logicState; // 0 = Inactive comm 1 = Active comm

reg [3:0] bitc;
reg [7:0] cframe;

always @(posedge sys_clk) begin
  if (!rst_n) begin
    frameReady = 1'b0;
    frame = 8'h00;
    
    sdapulldown = 1'b0;
    
    cstate = 2'b00;
    stateq = 6'h00;
    logicState = 1'b0;
  end else begin
    lstate = cstate;
    cstate = { sda, scl };
    if (stateq[1:0] != cstate) begin
      stateq = { stateq[3:0], cstate };
    end
    if (logicState == 1) begin
      if (stateq == STOP) begin
        logicState = 0;
        bitc = 3'b000;
      end else begin
        if (bitc == 4'd8) begin
          sdapulldown = 1'b1;
          if ((cstate != lstate) && (!scl)) begin
            sdapulldown = 1'b0;
            bitc = 3'd0;
            frame = cframe;
            frameReady = 1'b1;
          end
        end else begin
          if ((cstate != lstate) && (scl)) begin
            cframe = { cframe[6:0], sda };
            bitc = bitc + 1;
          end
        end
      end
    end else begin
      if (stateq == START) begin
        bitc = 3'b000;
        logicState = 1;
      end
    end
  end
end

endmodule
