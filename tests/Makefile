export PYTHONPATH = .

MTI_HOME = /home/g174911/modelsim/modeltech

INC_PATH      = -I$(MTI_HOME)/include
INC_PATH     += -I/home/g174911/tools/include/python2.7
LIB_PATH      = -L/home/g174911/tools/lib
LIB_REF       = -lpython2.7 -lm -ldl

SRC_C         = ../src/pyvpi.c
all : clean comp vpi run

clean :
    rm -rf wlft* work *.wlf *.so *.o

comp :
    vlib work
    vlog prim.v dff.v top.v

vpi : $(SRC_C)
    gcc -g -fPIC $(INC_PATH)  \
    $(LIB_PATH) $(LIB_REF) -shared -o pyvpi.so \
    $(SRC_C)

run :
    vsim -c -do vsim.do top -pli pyvpi.so
