#! python
import pyvpi
import sv_vpi_user as cons
trgobj=pyvpi.HandleByName("top.sreg",0)
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
cb_h = pyvpi.RegisterCb(cb)
print "get cb info"
# This function will case error, because this trgobj will be release twice.
# a = pyvpi.GetCbInfo(cb_h)
# print hex(cb.trgobj._handle),"0"
# print hex(a.trgobj._handle),"1"
