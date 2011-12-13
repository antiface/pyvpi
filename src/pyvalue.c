//The 
#include "pyvalue.h"

void pyvpi_value_Dealloc(p_pyvpi_value self)
{
    //Free self.
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds)
{
    self->_vpi_value.format = vpiHexStrVal;
    static char *kwlist[] = {"format", NULL};
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
