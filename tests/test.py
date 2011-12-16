#! python
import pyvpi
import sv_vpi_user as cons
print dir(pyvpi)
print pyvpi.HandleByName("top.sreg",0)
print pyvpi.HandleByName("top.sreg",0)
cb = pyvpi.CbData()
print type(cb)
cb.reason = cons.cbAtEndOfSimTime
cb.trgobj = pyvpi.HandleByName("top.sreg",0)
def callback(arg):
    print "callback is run..."
print dir(cb)
cb.callback = callback
print "Before RegisterCb."
cb_h = pyvpi.RegisterCb(cb)
print "After RegisterCb."
