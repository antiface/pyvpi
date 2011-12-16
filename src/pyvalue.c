//The 
#include "pyvalue.h"

void pyvpi_value_Dealloc(p_pyvpi_value self)
{
    //Free self.
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds)
{    
    static char *kwlist[] = {"format", NULL};
    self->_vpi_value.format = vpiHexStrVal; //Default value.
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,                                      
                                      &self->_vpi_value.format))
        return -1;
    return 0;
}

PyObject * pyvpi_value_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    p_pyvpi_value   self;
    self = (p_pyvpi_value)type->tp_alloc(type, 0);
    return (PyObject *) self;
}


//Get/Set
PyObject * s_pyvpi_value_getvalue(s_pyvpi_value *self, void *closure)
{
    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:
            //Need malloc new space or not??
            return Py_BuildValue("s",self->_vpi_value.value.str);
        case vpiScalarVal:
            return Py_BuildValue("i",self->_vpi_value.value.scalar);
        case vpiIntVal:
            return Py_BuildValue("i",self->_vpi_value.value.integer);
        case vpiRealVal:
            return Py_BuildValue("d",self->_vpi_value.value.real);
        case vpiVectorVal:  //TBD
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            Py_INCREF(Py_None);
            return Py_None;
    }
}
int        s_pyvpi_value_setvalue(s_pyvpi_value *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set index to NULL.");
        return -1;
    }
//    if (! PyInt_Check(value)) {
//        PyErr_SetString(PyExc_TypeError,
//                        "The index must be a int.");
//        return -1;
//    }
    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:
            //Need malloc new space or not??
            
        case vpiScalarVal:
            
        case vpiIntVal:
            
        case vpiRealVal:
            
        case vpiVectorVal:  //TBD
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            return -1;
    }
}
