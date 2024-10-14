`timescale 1ns / 1ps

module main(
    input wire sys_clk,
    input wire rst_n,
    input wire button_1,
    output wire led_1,
    output wire led_2,
    inout wire sda,
    input wire scl);

reg l1, l2; 
assign led_1 = l1;
assign led_2 = l2;

localparam FRAMECOUNT = 7;
wire [7:0]creg;
wire [7:0]regs[0:FRAMECOUNT];
i2c_slave #(.FRAMECOUNT(FRAMECOUNT)) slave (
    .rst_n(rst_n),
    .sda(sda), 
    .scl(scl),
    .creg(creg),
    .regs(regs)
  );
    
reg kmsscl;
always @(posedge sys_clk) begin
  if (!rst_n) begin
    l1 <= button_1;
    l2 <= 1'b0;
    kmsscl <= 1'b0;
  end else begin
    kmsscl <= scl;
    l1 <= kmsscl ^
      creg[0] ^ creg[1] ^ creg[2] ^ creg[3] ^ creg[4] ^ creg[5] ^ creg[6] ^ creg[7] ^ 
      regs[0][0] ^ regs[0][1] ^ regs[0][2] ^ regs[0][3] ^ regs[0][4] ^ regs[0][5] ^ regs[0][6] ^ regs[0][7] ^
      regs[1][0] ^ regs[1][1] ^ regs[1][2] ^ regs[1][3] ^ regs[1][4] ^ regs[1][5] ^ regs[1][6] ^ regs[1][7] ^
      regs[2][0] ^ regs[2][1] ^ regs[2][2] ^ regs[2][3] ^ regs[2][4] ^ regs[2][5] ^ regs[2][6] ^ regs[2][7] ^
      regs[3][0] ^ regs[3][1] ^ regs[3][2] ^ regs[3][3] ^ regs[3][4] ^ regs[3][5] ^ regs[3][6] ^ regs[3][7] ^
      regs[4][0] ^ regs[4][1] ^ regs[4][2] ^ regs[4][3] ^ regs[4][4] ^ regs[4][5] ^ regs[4][6] ^ regs[4][7] ^
      regs[5][0] ^ regs[5][1] ^ regs[5][2] ^ regs[5][3] ^ regs[5][4] ^ regs[5][5] ^ regs[5][6] ^ regs[5][7] ^
      regs[6][0] ^ regs[6][1] ^ regs[6][2] ^ regs[6][3] ^ regs[6][4] ^ regs[6][5] ^ regs[6][6] ^ regs[6][7] ^
      regs[7][0] ^ regs[7][1] ^ regs[7][2] ^ regs[7][3] ^ regs[7][4] ^ regs[7][5] ^ regs[7][6] ^ regs[7][7];
    l2 <= button_1;
  end
end

endmodule

