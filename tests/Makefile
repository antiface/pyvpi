export PYTHONPATH = .

MTI_HOME = /home/g174911/modelsim/modeltech

INC_PATH      = -I$(MTI_HOME)/include
INC_PATH     += -I/home/g174911/tools/include/python2.7
LIB_PATH      = -L/home/g174911/tools/lib -L$(MTI_HOME)/linux_x86_64
LIB_REF       = -lpython2.7 -lvsim -lm -ldl -lutil

SRC_C         = ../src/pyvpi.c
all : clean comp vpi run

clean :
	rm -rf wlft* work *.wlf *.so *.o

comp :
	vlib work
	vlog prim.v dff.v top.v

vpi : $(SRC_C)
	gcc -c -g $(INC_PATH) -fPIC -o pyvpi.o $(SRC_C)
	ld $(LIB_PATH) $(LIB_REF) -shared -o pyvpi.so \
	pyvpi.o

run :
	vsim -c -do vsim.do top -pli pyvpi.so
