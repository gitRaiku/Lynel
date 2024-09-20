`timescale 1ns / 1ps

module main(
    input sys_clk,
    input rst_n,
    input button_1,
    output led_1,
    output led_2);

reg [31:0]tim;
reg [1:0]leds;
assign led_1 = leds[0];
assign led_2 = leds[1];
reg lb;

always @(posedge sys_clk) begin
  if (!rst_n) begin
    tim <= 32'h00000000;
    leds <= 2'b00;
    lb <= 1'b0;
  end else begin
    if (!button_1) begin
        if (!lb) begin
            leds <= leds + 1;
        end
        lb <= 1'b1;
    end else begin
        lb <= 1'b0; 
        if (tim == 10000000) begin
          tim <= 32'h00000000;
          leds <= leds + 1;
        end else begin
          tim <= tim + 1;
        end
    end
  end
end

endmodule

