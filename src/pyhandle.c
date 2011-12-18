#include "pyhandle.h"

PyTypeObject pyvpi_handle_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._handle",              /*tp_name*/
    sizeof(s_pyvpi_handle),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_handle_Dealloc, /*tp_dealloc*/    
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
    "pyvpi handle objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_handle_methods,       /* tp_methods */
    pyvpi_handle_members,       /* tp_members */
    pyvpi_handle_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_handle_Init, /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_handle_New,           /* tp_new */
};


void pyvpi_handle_Dealloc(p_pyvpi_handle self)
{
    //Free self.
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Handle is release,ptr is <0x%lx>.\n",self);
#endif
    if(self->_vpi_handle != NULL) vpi_release_handle(self->_vpi_handle);
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_handle_Init(s_pyvpi_handle *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};
    
    PyErr_SetString(PyExc_TypeError,  "Error, you can't new a Handle object.");
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Handle is Initial.\n");
#endif
    Py_DECREF(self);
    return -1;
}

PyObject * pyvpi_handle_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{   
    p_pyvpi_handle self = (p_pyvpi_handle)type->tp_alloc(type, 0);
    self->_vpi_handle = NULL;
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Handle is allocate,ptr is <0x%lx>, type ptr is <0x%lx>.\n",self,type);
#endif
    return (PyObject *) self;
}

