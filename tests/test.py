#! python
import pyvpi
import sv_vpi_user as cons
cb = pyvpi.CbData()
val = pyvpi.Value()
cb.reason = cons.cbValueChange
#val.format = cons.vpiBinStrVal
cb.value  = val
cb.trgobj = pyvpi.HandleByName("top.sreg",0)
def callback(arg):
    print arg.value.value
    print "callback is run..."
cb.callback = callback
cb_h = pyvpi.RegisterCb(cb)
