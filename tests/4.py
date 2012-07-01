#! python
from pyvpi import CbData,registerCb,removeCb,handleByName,Value,getValue,printf
import pyvpi_cons as cons
import traceback

o = handleByName("test.o")
a = handleByName("test.a")
b = handleByName("test.b")
def callback(self) :
    try :
        getValue(self.a,self.av)
        getValue(self.b,self.bv)
        printf("%s : %s(a) + %s(b) = %s(o)\n" % (self.time.time,
            self.av.value,
            self.bv.value,
            self.value.value.vec))
    except Exception,e :
        printf("%s\n%s\n" % (e,traceback.print_exc()))
        
cb = CbData(trgobj = o,callback = callback, value = Value(cons.vpiVectorVal))
cb.a = a
cb.b = b
cb.av = Value()
cb.bv = Value()
printf("%s\n"  % (hasattr(cb,"a")))
registerCb(cb)

