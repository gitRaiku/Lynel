`timescale 1ns / 1ps

module tristate(pin, in, out, oe);
    inout wire pin;
    output wire in;
    input wire out;
    input wire oe;

    assign in = pin;
    assign pin = oe ? out : 1'bz;
endmodule

