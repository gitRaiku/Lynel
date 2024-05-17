module usb_read(
  input clk12,
  input enabled,
  inout dp,
  inout dm
);

reg[1:0] lastState; // { dp, dm }

always @(posedge clk12) begin
  if (!enabled) begin
    lastState <= 2'b00;
  end else begin
    case ({lastState[0], lastState[1], dp, dm})
      4'b0000:
      4'b0001:
      4'b0010:
      4'b0010:
      4'b0010:
      4'b0010:
      4'b0010:
      4'b0010:
      4'b0010:
    endcase

    lastState <= { dp, dm }
  end
  
end

endmodule
