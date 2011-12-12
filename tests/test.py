#! python
print "Hello python."
from ctypes import *
vpi = cdll.LoadLibrary("pyvpi.so")
print vpi.pyvpi_printf()
print "Python end."
vsim = cdll.LoadLibrary("/home/g174911/modelsim/modeltech/linux_x86_64/libvsim.so")
print vsim.vpi_printf("Hello vsim.\n")
import pyvpi
print "30s later."
