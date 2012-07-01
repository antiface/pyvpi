#! python
import pyvpi
import pyvpi_cons as cons
pyvpi.setDebugLevel(30)
a = pyvpi.handleByName("test.a")
b = pyvpi.handleByName("test.b")
o = pyvpi.handleByName("test.o")
val_a = pyvpi.Value()
val_b = pyvpi.Value(cons.vpiVectorVal)
val_o = pyvpi.Value(cons.vpiVectorVal)
pyvpi.getValue(a,val_a)
pyvpi.getValue(b,val_b)
pyvpi.getValue(o,val_o)
pyvpi.printf("a[{}] + b{} = o{}\n".format(val_a.value,val_b.value.vec,val_o.value.vec))
