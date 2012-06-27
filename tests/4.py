#! python
from pyvpi import CbData,registerCb,removeCb,handleByName,Value,getValue,printf
import pyvpi_cons as cons

o = handleByName("test.o")
a = handleByName("test.a")
b = handleByName("test.b")
def callback(self) :
    getValue(self.user_data[0],self.user_data[2])
    getValue(self.user_data[1],self.user_data[3])
    printf("%s : %s(a) + %s(b) = %s(o)\n" % (self.time.low,
        self.user_data[2].value,
        self.user_data[3].value,
        self.value.value))
        
cb = CbData(trgobj = o,callback = callback, value = Value(cons.vpiBinStrVal))
cb.user_data = [a,b,Value(),Value()]
registerCb(cb)

