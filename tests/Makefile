export PYTHONPATH += .:../src/pyvpi

ifeq ($(OS),Windows_NT)
    DES_TARGET    := pyvpi.pyd
else
    DES_TARGET    := pyvpi.so
endif

INC_PATH      = -I$(MTI_HOME)/include
INC_PATH     += -I/usr/include/python2.7
LIB_PATH      = -L/usr/lib
LIB_REF       = -lpython2.7 -lm -ldl -lutil
CFLAGS        = -c -g $(INC_PATH) -fPIC
SRC_C         = ../src/pyvpi.c \
                ../src/pyvalue.c \
                ../src/pytime.c \
                ../src/pystrength.c \
                ../src/pyvector.c   \
                ../src/pyhandle.c   \
                ../src/pycbdata.c   \
                ../src/pydelays.c	\
				../src/pysystfdata.c

SRC_O         = pyvpi.o \
                pyvalue.o \
                pycbdata.o \
                pytime.o \
                pystrength.o \
                pyvector.o  \
                pyhandle.o  \
                pydelays.o	\
				pysystfdata.o

ifeq ($(OS),Windows_NT)
    all : clean comp run
else
    all : clean comp vpi run
endif

clean :
	rm -rf wlft* work *.wlf *.so *.o

comp :
	vlib work
	vlog prim.v dff.v top.v

vpi : $(SRC_C)
	gcc $(CFLAGS) $(SRC_C)
	ld $(LIB_PATH) $(LIB_REF) -shared -o pyvpi.so \
	$(SRC_O)

run :
	vsim -c -do vsim.do test -pli $(DES_TARGET)    