#! python
import pyvpi
import sv_vpi_user as cons
import random
import unittest
import sys
import gc
import os.path

sys.path.insert(0,os.path.realpath(".") + "\\pyeda\\src")
import pyeda

def test_vector() :
    vec = pyvpi.Vector()
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))
    vec = pyvpi.Vector(8)
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))
    vec = pyvpi.Vector(8,[(511,125465)])
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))
    vec = pyvpi.Vector(8,[511])
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))
    vec.vec = [5156]
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))
    vec.size = 30
    pyvpi.printf("%s %s\n" % (vec.vec,vec.size))

def test_time() :
    time = pyvpi.Time()    
    
def test_pyeda() :            
    #print "???"
    pyvpi.printf("1\n")
    pyvpi.handleByName("test")
    pyvpi.printf("2\n")
    a = pyvpi.handleByName("o")
    pyvpi.printf("3\n")    
    pyvpi.printf("module name : %s\n" %
                 pyvpi.getStr(cons.vpiFullName,
                              pyvpi.handle(cons.vpiModule, a)
                              )
                 )
    pyvpi.printf("4\n")
    val = pyvpi.Value(cons.vpiVectorVal)
    vec = pyvpi.Vector(9,[(0,0)])
    val.value = vec
    #pyvpi.putValue(a,val)
    pyvpi.printf("%s %s\n" %  (val.value.vec,val.value.size))

def test_index():
    o = pyvpi.handleByName("test.o")
    o_0 = pyvpi.handleByIndex(o,0)
    pyvpi.printf("index : %s\n" % o_0)
    o1 = pyvpi.handleByName("test.o[0]")
    pyvpi.printf("index : %s\n" % o1)

def test_iterate():
    m = pyvpi.handleByName("test")
    iter = pyvpi.iterate(cons.vpiReg,m)
    reg = pyvpi.scan(iter)
    while(reg) :
        pyvpi.printf("reg : %s\n" % pyvpi.getStr(cons.vpiName,reg))
        reg = pyvpi.scan(iter)

def test_normal() :
    """
    """  
    global call
    pyvpi.printf("error start!\n")
    cb = pyvpi.CbData(cons.cbValueChange,
                      trgobj = pyvpi.handleByName("test.o",0),
                      value  = pyvpi.Value(cons.vpiBinStrVal))
    cb.user_data = 1
    def callback(arg):
        pyvpi.printf("%s : " % arg.time.low)
        pyvpi.printf("%s : " % arg.value.value)        
        pyvpi.printf("%s\n" % "callback is run...")
        if cb.user_data == 3 :
            pyvpi.removeCb(arg)
        cb.user_data += 1
    cb.callback = callback
    pyvpi.registerCb(cb)
    # This function will case error, because this trgobj will be release twice.
    #pyvpi.getCbInfo(cb_h)

def test_systfdata() :
    """
    """
    def calltf(self) :
        print self.tfname
    systfdata = pyvpi.SysTfData()
    systfdata.tfname = "$abc"
    systfdata = pyvpi.SysTfData(tfname = "$abc")
    systfdata.calltf = calltf
    pyvpi.registerSysTf(systfdata)
    
if __name__ == '__main__'     :
    test_vector()
    test_time()    
    test_normal()
    test_pyeda()
    test_index()
    test_iterate()