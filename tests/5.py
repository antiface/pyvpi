#! python
import pyvpi
import pyvpi_cons as cons
import random
import unittest
import sys
import socket
import select

host = "localhost"
port = 9999

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((host,port))
trgobj=pyvpi.handleByName("test.clk",0)
cb = pyvpi.CbData(trgobj=trgobj)
val = pyvpi.Value()
cb.reason = cons.cbValueChange
cb.value  = val
cb.user_data = [s,0]
def callback(arg) :
    cb.user_data[0].send("%s\n" % cb.user_data[1])
    infds,outfds,errfds = select.select([cb.user_data[0],],[],[],0)
    if len(infds) > 0 :
        buf = cb.user_data[0].recv(8196)
        print buf
    cb.user_data[1] += 1
cb.callback = callback
cb_h = pyvpi.registerCb(cb)