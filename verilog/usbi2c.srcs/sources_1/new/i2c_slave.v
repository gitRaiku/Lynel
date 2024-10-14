`timescale 1ns / 1ps

// Code generously partially copied from https://github.com/jiacaiyuan/i2c_slave

module i2c_slave #(parameter FRAMECOUNT=7, [6:0]device_address=7'b0011010) 
  (input rst_n, inout sda, input scl,
   output reg [7:0]regs[0:FRAMECOUNT], output reg [7:0]creg);

reg start_detect, start_resetter;
wire start_rst = ~rst_n | start_resetter;//detect the START for one cycle
always @(posedge start_rst or negedge sda) begin
  if (start_rst) start_detect <= 1'b0;
  else start_detect <= scl;
end

always @(negedge rst_n or posedge scl) begin
  if (!rst_n) start_resetter <= 1'b0;
  else start_resetter <= start_detect; // Pulls start_rst high
end

reg stop_detect, stop_resetter;
wire stop_rst = ~rst_n | stop_resetter;//detect the STOP for one cycle
always @(posedge stop_rst or posedge sda) begin   
  if (stop_rst) stop_detect <= 1'b0;
  else stop_detect <= scl;
end

always @(negedge rst_n or posedge scl) begin   
  if (!rst_n) stop_resetter <= 1'b0;
  else stop_resetter <= stop_detect; // Pulls stop_rst high
end

reg [3:0]bit_counter;
wire lsb_bit = (bit_counter == 4'h7) && !start_detect;//the 8bits one byte data
wire ack_bit = (bit_counter == 4'h8) && !start_detect;//the 9bites ack 

always @(negedge scl) begin
  if (ack_bit || start_detect) bit_counter <= 4'h00;
  else bit_counter <= bit_counter + 4'h01;
end

reg master_ack;
reg [7:0]input_shift;
wire address_detect = (input_shift[7:1] == device_address);//the input address match the slave
wire read_write_bit = input_shift[0];// the write or read operation 0=write and 1=read
always @(posedge scl) begin
  if (!ack_bit) input_shift <= { input_shift[6:0], sda };
  else master_ack <= ~sda; // If sda is high then no ack was recieved
end

localparam STATE_IDLE      = 3'h0;//idle
localparam STATE_DEV_ADDR  = 3'h1;//the slave addr match
localparam STATE_READ      = 3'h2;//the op=read 
localparam STATE_IDX_PTR   = 3'h3;//get the index of inner-register
localparam STATE_WRITE     = 3'h4;//write the data in the reg 

reg [2:0]state;
integer i;
always @(negedge rst_n or negedge scl) begin
  if (!rst_n) begin
    state <= STATE_IDLE;
    creg <= 8'h00;
    for (i = 0; i <= FRAMECOUNT; i = i + 1) begin regs[i] <= 8'h00; end 
  end
  else if (start_detect) begin state <= STATE_DEV_ADDR; creg <= 8'h00; end
  else if (ack_bit) begin
    regs[creg] <= input_shift;
    creg <= creg + 1;
    case (state) 
      STATE_IDLE: state <= STATE_IDLE;
      STATE_DEV_ADDR:
        if (!address_detect) state <= STATE_IDLE;
        else state <= read_write_bit ? STATE_READ : STATE_IDX_PTR;
      STATE_READ:
        if (master_ack) state <= STATE_READ;
        else state <= STATE_IDLE;
      STATE_IDX_PTR: state <= STATE_WRITE;
      STATE_WRITE: state <= STATE_WRITE;
    endcase
  end
  else if (stop_detect) begin state <= STATE_IDLE; creg <= 8'h00; end
end


reg [7:0]output_shift;
always @(negedge scl) begin
  if (lsb_bit) begin
    /// Get the next output byte
  end else output_shift <= { output_shift[6:0], 1'b0 };
end

reg output_control, sdav;
assign sda = output_control ? sdav : 1'bz;
always @(negedge rst_n or negedge scl) begin
  if (!rst_n) begin
    output_control <= 1'b0;
    sdav <= 1'b0;
  end else begin
    if (start_detect) output_control <= 1'b0;
    else if (lsb_bit) begin 
      sdav <= 1'b0;
      output_control <= (
                        ((state == STATE_DEV_ADDR) && address_detect) ||
                        (state == STATE_IDX_PTR) ||
                        (state == STATE_WRITE)); 
    end else if (ack_bit) begin
      sdav <= 1'b0;
      if (
        ((state == STATE_READ) && master_ack) || 
        ((state == STATE_DEV_ADDR) && address_detect && read_write_bit)) begin
        output_control <= !output_shift[7];
      end else output_control <= 1'b0;
    end else if (state == STATE_READ) begin
      sdav <= 1'b0;
      output_control <= !output_shift[7];
    end else output_control <= 1'b0;
  end
end

endmodule
