#include "pytime.h"

PyTypeObject pyvpi_time_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.Time",              /*tp_name*/
    sizeof(s_pyvpi_time),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_time_Dealloc, /*tp_dealloc*/    
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "pyvpi time objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_time_methods,       /* tp_methods */
    pyvpi_time_members,       /* tp_members */
    pyvpi_time_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_time_Init, /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_time_New,           /* tp_new */
};


void pyvpi_time_Dealloc(p_pyvpi_time self)
{
    //Free self.
    pyvpi_verbose(sprintf(print_buffer, "pyvpi.Time is release,ptr is <0x%lx>.\n",self));
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_time_Init(s_pyvpi_time *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"type", NULL};
    
    self->_vpi_time.type = vpiSimTime; //Default value.
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,                                      
                                      &self->_vpi_time.type))
    {
        PyErr_SetString(VpiError, "The pyvpi.Time initial args must be "
            "(type = int).");
        return -1;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi.Time is Initial,type is <0x%lx>.\n",
        self->_vpi_time.type));
    return 0;
}

PyObject * pyvpi_time_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{   
    p_pyvpi_time self = (p_pyvpi_time)type->tp_alloc(type, 0);
    pyvpi_verbose(sprintf(print_buffer, "pyvpi.Time is allocate, "
                                      "ptr is <0x%lx>, type ptr is <0x%lx>.\n",self,type));
    return (PyObject *) self;
}


PyObject * s_pyvpi_time_gettime(s_pyvpi_time *self, void *closure)
{   
    long long time = self->_vpi_time.high;
    time = (time<< 32) + self->_vpi_time.low;
    return Py_BuildValue("k",time);
}
