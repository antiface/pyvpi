export PYTHONPATH += .:../src


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

all : clean comp vpi run

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
	vsim -c -do vsim.do top -pli pyvpi.so
