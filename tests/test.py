#! python
import pyvpi
import sv_vpi_user as cons
import random
import unittest
import sys

class TestFunction(unittest.TestCase) :
    def test_normal(self) :
        """
        """
        trgobj=pyvpi.handleByName("top.sreg",0)
        print "handle first allocate."
        cb = pyvpi.CbData(trgobj=trgobj)
        val = pyvpi.Value()
        cb.reason = cons.cbValueChange
        #val.format = cons.vpiBinStrVal
        cb.value  = val
        print hex(cb.trgobj._handle)
        def callback(arg):
            print arg.value.value
            print arg.time.low
            print "callback is run..."
        cb.callback = callback
        cb_h = pyvpi.registerCb(cb)
        print "handle second allocate."
        a = cb_h
        print "get cb info"
        # This function will case error, because this trgobj will be release twice.
        pyvpi.getCbInfo(cb_h)
        #print "handle third allocate."
        #print hex(cb.trgobj._handle),"0"
        #print hex(a.trgobj._handle),"1"

    def test_systfdata(self) :
        """
        """
        def calltf(self) :
            print self.tfname
        systfdata = pyvpi.SysTfData()
        systfdata.tfname = "$abc"
        systfdata = pyvpi.SysTfData(tfname = "$abc")
        print systfdata.tfname
        systfdata.calltf = calltf
if __name__ == '__main__'     :
    unittest.main()
