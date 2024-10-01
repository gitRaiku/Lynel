`timescale 1ns / 1ps

module i2c_slave(
    input sys_clk, input rst_n,
    inout sda, input scl,
    output reg [7:0]frames[0:4], output reg doneframe
    );

reg lsda;
reg [7:0]start;

reg writeEnabled, csda;
//assign sda = 1'bz;
assign sda = writeEnabled ? csda : 1'bz;

localparam ADDR = 7'b0011010;

reg [5:0]state;

localparam STATE_PD0 = 6'd20;
localparam STATE_PD1 = 6'd21;

always @(posedge sys_clk) begin
  if (!rst_n) begin
    lsda <= 1'b0;
    start <= 8'h00;
    writeEnabled <= 1'b0;
    csda <= 1'b0;
    for (i = 0; i < 4; i = i + 1) frames[i] <= 8'h00;
    frames[0] <= 7'h00;
    state <= 6'h00;
    doneframe <= 0;
  end
end

always @(posedge sda) begin
  if (scl == 1 && start == 1) begin // STOP Signal
    start <= 8'h00; writeEnabled <= 1'b0;
    state <= 0;
    if (frames[0][6:0] == ADDR) begin
      doneframe <= 1;
    end
  end
end

always @(negedge sda) begin 
  if (state == STATE_PD0) begin // Start ACK signal
    csda <= 1'b0; writeEnabled <= 1'b1;
    state <= STATE_PD1;
  end else if (scl == 1 && start == 0) begin // START Signal
    start <= 7'h01; writeEnabled <= 1'b0;
    state <= 6'h00; 
  end
end

always @(posedge scl) begin
  if (start > 0) begin
    if ((state >= 0) && (state <= 7)) begin
      frames[start][state] <= sda;
      state <= state + 1;
    end
  end
end

always @(negedge scl) begin
  if (state == 8) begin
    if (frames[0][6:0] == ADDR) begin // Start ACK signal now or when sda falls
      doneframe <= 0;
      for (i = 1; i < 4; i = i + 1) frames[i] <= 8'h00;
      if (sda) begin
          state <= STATE_PD0;
      end else begin
          csda <= 1'b0; writeEnabled <= 1'b1;
          state <= STATE_PD1;
      end
    end else begin
      state <= 0;
      start <= 0;
    end
  end else if (state == STATE_PD1) begin // Stop ACK signal
    writeEnabled <= 1'b0;
    state <= 0;
    start <= 1;
  end
end

endmodule
