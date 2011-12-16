#ifndef __PYTIME_H__
#define __PYTIME_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"
//typedef struct t_vpi_time
//{
//  PLI_INT32  type;               /* [vpiScaledRealTime, vpiSimTime,
//                                     vpiSuppressTime] */
//  PLI_UINT32 high, low;          /* for vpiSimTime */
//  double     real;               /* for vpiScaledRealTime */
//} s_vpi_time, *p_vpi_time;

/* ------------------------------------------------------------------------- */
//PyObject vpi time struct data.
//PyObject vpi time struct data.
typedef struct t_pyvpi_time
{
    PyObject_HEAD
    s_vpi_time  _vpi_time;      //struct vpi time.
} s_pyvpi_time, *p_pyvpi_time;

void pyvpi_time_Dealloc(p_pyvpi_time self);
int  pyvpi_time_Init(s_pyvpi_time *self, PyObject *args, PyObject *kwds);
PyObject * pyvpi_time_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

static PyMethodDef  pyvpi_time_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_time_members[]  = {
    {"type",  T_INT,    offsetof(s_pyvpi_time, _vpi_time.type), 0, "time type[vpiScaledRealTime, vpiSimTime,vpiSuppressTime]"},
    {"high",  T_UINT,   offsetof(s_pyvpi_time, _vpi_time.high), 0, "high bits for vpiSimTime"},
    {"low",   T_UINT,   offsetof(s_pyvpi_time, _vpi_time.low), 0, "low bits for vpiSimTime"},
    {"real",  T_DOUBLE, offsetof(s_pyvpi_time, _vpi_time.real), 0, "real time for vpiScaledRealTime"},
    {NULL}
};
static PyGetSetDef pyvpi_time_getsets[]  = {
    {NULL}
};

static PyTypeObject pyvpi_time_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._Time",              /*tp_name*/
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
    (initproc) pyvpi_time_Init,      /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_time_New,           /* tp_new */
};

#endif