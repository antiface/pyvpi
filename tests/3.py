#! python
import pyvpi
import pyvpi_cons as cons
def getAllHandles(handle,type) :
    ans = []
    iter = pyvpi.iterate(type,handle)
    while True :
        h = pyvpi.scan(iter)
        if not h :
            break
        ans.append(h)
    return ans
    
mod = pyvpi.handleByName("test")

pyvpi.printf("All regs are blew here :\n")    
for reg in getAllHandles(mod,cons.vpiReg) :
    pyvpi.printf("%s\n" % (pyvpi.getStr(cons.vpiName,reg)))
pyvpi.printf("All nets are blew here :\n")    
for net in getAllHandles(mod,cons.vpiNet) :
    pyvpi.printf("%s\n" % (pyvpi.getStr(cons.vpiFullName,net)))