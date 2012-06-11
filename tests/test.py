#! python
import pyvpi
import sv_vpi_user as cons
import random
import unittest
import sys
import gc

sys.path.insert(0,"pyeda/src")

def test_pyeda() :
    print "a"
    import pyeda
    print "b"
    a = pyvpi.handleByName("test.o",0)
    c = a
    del a
    gc.collect()
    b = pyvpi.handleByName("test.o",0)
    gc.collect()
        
def test_normal() :
    """
    """
    trgobj=pyvpi.handleByName("top.sreg",0)
    cb = pyvpi.CbData(trgobj = trgobj)
    cb.reason = cons.cbValueChange
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
    test_pyeda()
