export PYTHONPATH = .:../src


INC_PATH      = -I$(MTI_HOME)/include
INC_PATH     += -I$(PY_HOME)/include/python2.7
LIB_PATH      = -L$(PY_HOME)/lib
LIB_REF       = -lpython2.7 -lm -ldl -lutil
CFLAGS        = -c -g $(INC_PATH) -fPIC
SRC_C         = ../src/pyvpi.c ../src/pyvalue.c ../src/pycbdata.c
SRC_O         = pyvpi.o pyvalue.o pycbdata.o

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
