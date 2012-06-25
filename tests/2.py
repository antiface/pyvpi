#! python
import pyvpi
import pyvpi_cons as cons
pyvpi.setDebugLevel(30)
a = pyvpi.handleByName("test.a")
b = pyvpi.handleByName("test.b")
o = pyvpi.handleByName("test.o")
val_a = pyvpi.Value()
val_b = pyvpi.Value()
val_o = pyvpi.Value()
pyvpi.getValue(a,val_a)
pyvpi.getValue(b,val_b)
pyvpi.getValue(o,val_o)
pyvpi.printf("a[0x{}] + b[0x{}] = o[0x{}]\n".format(val_a.value,val_b.value,val_o.value))
val_b.value = val_o.value
pyvpi.putValue(b,val_b)