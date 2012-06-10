#! python
import pyvpi
import sv_vpi_user as cons
import random
import unittest
import sys

def test_normal() :
    """
    """
    trgobj=pyvpi.handleByName("top.sreg",0)
    cb = pyvpi.CbData(trgobj=trgobj)
    val = pyvpi.Value()
    cb.reason = cons.cbValueChange
    #val.format = cons.vpiBinStrVal
    cb.value  = val
    def callback(arg):
        print arg.value.value
        print arg.time.low
        print "callback is run..."
    cb.callback = callback
    cb_h = pyvpi.registerCb(cb)
    a = cb_h
    # This function will case error, because this trgobj will be release twice.
    pyvpi.getCbInfo(cb_h)

def test_systfdata() :
    """
    """
    def calltf(self) :
        print self.tfname
    systfdata = pyvpi.SysTfData()
    systfdata.tfname = "$abc"
    systfdata = pyvpi.SysTfData(tfname = "$abc")
    systfdata.calltf = calltf
if __name__ == '__main__'     :
    test_normal()
