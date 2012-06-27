//
// Copyright 1991-2010 Mentor Graphics Corporation
//
// All Rights Reserved.
//
// THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION WHICH IS THE PROPERTY OF 
// MENTOR GRAPHICS CORPORATION OR ITS LICENSORS AND IS SUBJECT TO LICENSE TERMS.
//   
// ----------------------------------

`timescale 1ns / 1ns

module top ( ain );
inout [3:0] ain;

parameter left = 16;
parameter right = 14;

tri  wire01;
wand wire02;

reg       sreg;
reg [4:2] areg;
time      treg;
integer   ireg;
real      rreg;
realtime  rtreg;

reg       msreg [left:right];
reg [3:1] mareg [left+1:right+2];
time      mtreg [left-1:right-2];
integer   mireg [2:3];

// ----- Task -----

task some_task;
  input a;
  output b;
  inout c;

reg       t_sreg;
reg [-2:1] t_areg;
time      t_treg;
integer   t_ireg;
real      t_rreg;
realtime  t_rtreg;

reg       t_msreg [left:right];
reg [4:1] t_mareg [left+1:right+2];
time      t_mtreg [left-1:right-2];
integer   t_mireg [2:3];

 begin
  b = a | c;
  c = b;
 end
endtask

// ----- Function -----

function invert;
  input i1;

reg       f_sreg;
reg [4:0] f_areg;
time      f_treg;
integer   f_ireg;
real      f_rreg;
realtime  f_rtreg;

reg       f_msreg [left:right];
reg [3:0] f_mareg [left+1:right+2];
time      f_mtreg [left-1:right-2];
integer   f_mireg [2:3];

 begin
  invert = ~i1;
 end
endfunction

// ----- Named Begin -----

initial begin : startup

reg       nb_sreg;
reg [1:3] nb_areg;
time      nb_treg;
integer   nb_ireg;
real      nb_rreg;
realtime  nb_rtreg;

reg       nb_msreg [left:right];
reg [-2:0] nb_mareg [left+1:right+2];
time      nb_mtreg [left-1:right-2];
integer   nb_mireg [2:3];

  $test();
  sreg = 1;
  #10 sreg = 2;
  $display("top display %d ",$time);
  $finish(0);
end

// ----- Named Fork -----

initial fork : fork_in_road

reg       k_sreg;
reg [6:5] k_areg;
time      k_treg;
integer   k_ireg;
real      k_rreg;
realtime  k_rtreg;

reg       k_msreg [left:right];
reg [1:5] k_mareg [left+1:right+2];
time      k_mtreg [left-1:right-2];
integer   k_mireg [2:3];

join

wire qval;
reg dval;
reg clear;
reg preset;
reg clock;

dff dff_inst( qval, dval, clear, preset, clock );

reg control, din;
wire udp_out;

sudp sudp_inst( udp_out, control, din );

wire muxout;
reg ctl, dA, dB;

multiplexer mult_inst( muxout, ctl, dA, dB );

endmodule

module test;
    reg clk;
    reg [7:0] a,b;
    wire  [8:0] o;
    
    assign o = a + b;
    
    always #5 clk = ~clk;
    
    initial begin
        $pyvpi_main("5.py");
        clk = 0;
        a   = 0;
        b   = 0;
        repeat(5) begin
        #5;
        a = a +1;
        end
        $finish(0);
    end
endmodule
