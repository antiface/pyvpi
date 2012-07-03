from pyvpi import *
from pyvpi_cons import *
import mmap
import ctypes
import traceback

with open("hello.map", "wb") as f:
    f.write("0")

o = handleByName("test.o")
a = handleByName("test.a")
b = handleByName("test.b")
def callback(self) :
    try :
        printf("gyx : %s \n" % self.cnt)
        if self.cnt < 10 :
            if self.cnt % 2 == 0 :
                self.bv.value += 1
                putValue(self.b,self.bv)
                self.time.low = 0
                #removeCb(self)
                registerCb(self)
            else :
                self.time.low = 5000
                #removeCb(self)
                registerCb(self)
        self.cnt += 1
    except Exception,e :
        removeCb(self)
        printf("%s\n%s\n" % (e,traceback.print_exc()))

cb = CbData(cbReadWriteSynch,callback = callback)
cb.time.low = 5000
cb.o = handleByName("test.o")
cb.a = handleByName("test.a")
cb.b = handleByName("test.b")
cb.bv = Value(vpiIntVal)
cb.cnt = 0
#| cb.file = open("hello.map", "r+b")
#| cb.map = mmap.mmap(cb.file.fileno(), 1024)
#| saddr = ctypes.addressof(ctypes.c_int.from_buffer(cb.map))
#| printf("saddr : %s %s\n" % (saddr,saddr+1024))
#| cb.value,saddr = createValueFromMMap(o,vpiVectorVal,saddr,saddr+1024)
#| printf("saddr : %s\n" % saddr)
#| printf("%s\n"  % (hasattr(cb,"a")))
registerCb(cb)

