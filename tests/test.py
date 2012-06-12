#! python
import pyvpi
import sv_vpi_user as cons
import random
import unittest
import sys
import gc

sys.path.insert(0,"pyeda/src")

def test_vector() :
    vec = pyvpi.Vector()
    print vec.vec,vec.size
    vec = pyvpi.Vector(8)
    print vec.vec,vec.size
    vec = pyvpi.Vector(8,[(511,125465)])
    print vec.vec,vec.size
    vec = pyvpi.Vector(8,[511])
    print vec.vec,vec.size
    vec.vec = [5156]
    print vec.vec,vec.size
    vec.size = 30
    print vec.vec,vec.size

def test_time() :
    time = pyvpi.Time()    
    
def test_pyeda() :
    import pyeda
    a = pyvpi.handleByName("test.o",0)    
    val = pyvpi.Value(cons.vpiVectorVal)
    vec = pyvpi.Vector(9,[(0,0)])
    val.value = vec
    #pyvpi.putValue(a,val)
    print val.value.vec,val.value.size
        
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
    test_vector()
    test_time()
