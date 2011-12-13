//
#include "Python.h"
#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyvalue.h"
/* ------------------------------------------------------------------------- */
//PyObject vpi time struct data.
typedef struct t_pyvpi_time
{
    PyObject_HEAD
    s_vpi_time  _vpi_time;      //struct vpi time.
} s_pyvpi_time, *p_pyvpi_time;

static PyTypeObject pyvpi_time_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.time",              /*tp_name*/
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

/* ------------------------------------------------------------------------- */
//PyObject vpi delay struct data.
typedef struct t_pyvpi_delay
{
    PyObject_HEAD
    s_vpi_delay  _vpi_delay;      //struct vpi time.
} s_pyvpi_delay, *p_pyvpi_delay;

static PyTypeObject pyvpi_delay_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.delay",             /*tp_name*/
    sizeof(s_pyvpi_delay),     /*tp_basicsize*/
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
    "pyvpi delay objects",     /* tp_doc */
};

/* ------------------------------------------------------------------------- */
//PyObject vpi vecval struct data.
typedef struct t_pyvpi_vecval
{
    PyObject_HEAD
    s_vpi_vecval  _vpi_vecval;      //struct vpi time.
} s_pyvpi_vecval, *p_pyvpi_vecval;

static PyTypeObject pyvpi_vecval_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.vecval",            /*tp_name*/
    sizeof(s_pyvpi_vecval),    /*tp_basicsize*/
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
    "pyvpi vecval objects",    /* tp_doc */
};

