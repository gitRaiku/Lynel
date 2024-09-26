`timescale 1ns / 1ps

module i2c_slave(
    inout sda,
    input scl
    );

reg lsda;
reg start;

reg writeEnabled, csda;
assign sda = writeEnabled ? csda : 1'bz;

reg [6:0]address;
reg [5:0]state;

always @(posedge sda) begin
  if (scl == 1 && start == 1) begin
    start <= 1'b0; writeEnabled <= 1'b0;
    state <= 0;
  end
end

always @(negedge sda) begin
  if (scl == 1 && start == 0) begin
    start <= 1'b0; writeEnabled <= 1'b0;
    state <= 0;
  end
end

always @(posedge scl) begin
  if (start) begin
    if ((state >= 0) && (state <= 7)) begin
      address[state] <= sda;
      state <= state + 1;
    end
    if (state == 9) begin
      state <= 0;
    end
  end
end

always @(negedge scl) begin
  if (state == 7) begin
    csda <= 1'b0; writeEnabled <= 1'b1;
    state <= state + 1;
  end else if (state == 8) begin
    writeEnabled <= 1'b0;
    state <= state + 1;
  end
end

endmodule
