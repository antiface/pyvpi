//
// Copyright 1991-2010 Mentor Graphics Corporation
//
// All Rights Reserved.
//
// THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION WHICH IS THE PROPERTY OF 
// MENTOR GRAPHICS CORPORATION OR ITS LICENSORS AND IS SUBJECT TO LICENSE TERMS.
//   

// ----- Combinational UDP -----

primitive multiplexer (mux, control, dataA, dataB);
output mux;
input control, dataA, dataB;
table
// control dataA dataB   mux
       0     1     0   :  1 ;
       0     1     1   :  1 ;
       0     1     x   :  1 ;
       0     0     0   :  0 ;
       0     0     1   :  0 ;
       0     0     x   :  0 ;
       1     0     1   :  1 ;
       1     1     1   :  1 ;
       1     x     1   :  1 ;
       1     0     0   :  0 ;
       1     1     0   :  0 ;
       1     x     0   :  0 ;
       x     0     0   :  0 ;
       x     0     1   :  x ;
       x     1     0   :  x ;
       x     1     1   :  1 ;
endtable
endprimitive

// ----- Sequential UDP -----

primitive sudp (ans, control, dataB);
output ans;
reg ans;
input control, dataB;
initial ans = 1;
table
//  control = 0 --> dataB OR p_ans
//  control = 1 --> dataB AND p_ans
//  control = x --> dataB
//  control dataB  p_ans   ans
       0      0  :  0   :  0 ;
       0      0  :  1   :  1 ;
       0      1  :  0   :  1 ;
       0      1  :  1   :  1 ;
       1      0  :  0   :  0 ;
       1      0  :  1   :  0 ;
       1      1  :  0   :  0 ;
       1      1  :  1   :  1 ;
       x      0  :  0   :  0 ;
       x      0  :  1   :  0 ;
       x      1  :  0   :  1 ;
       x      1  :  1   :  1 ;
       0      x  :  0   :  0 ;
       0      x  :  1   :  0 ;
       1      x  :  0   :  0 ;
       1      x  :  1   :  0 ;
       x      x  :  0   :  0 ;
       x      x  :  1   :  0 ;
endtable
endprimitive
