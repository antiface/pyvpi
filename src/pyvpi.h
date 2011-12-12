//
#include "Python.h"
#include "vpi_user.h"
#include "sv_vpi_user.h"

//PyObject vpi time struct data.
typedef struct t_pyvpi_time
{
    PyObject_HEAD
    s_vpi_time  _vpi_time;      //struct vpi time.
} s_pyvpi_time, *p_pyvpi_time;

static PyTypeObject pyvpi_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.vpi_time",          /*tp_name*/
    sizeof(s_pyvpi_time),      /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "pyvpi time objects",      /* tp_doc */
};