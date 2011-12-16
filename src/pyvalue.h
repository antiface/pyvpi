#ifndef __PYVALUE_H__
#define __PYVALUE_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"
//typedef struct t_vpi_value
//{
//  PLI_INT32 format; /* vpi[[Bin,Oct,Dec,Hex]Str,Scalar,Int,Real,String,
//                           Vector,Strength,Suppress,Time,ObjType]Val */
//  union
//    {
//      PLI_BYTE8                *str;       /* string value */
//      PLI_INT32                 scalar;    /* vpi[0,1,X,Z] */
//      PLI_INT32                 integer;   /* integer value */
//      double                    real;      /* real value */
//      struct t_vpi_time        *time;      /* time value */
//      struct t_vpi_vecval      *vector;    /* vector value */
//      struct t_vpi_strengthval *strength;  /* strength value */
//      PLI_BYTE8                *misc;      /* ...other */
//    } value;
//} s_vpi_value, *p_vpi_value;
/* ------------------------------------------------------------------------- */
//PyObject vpi time struct data.
typedef struct t_pyvpi_value
{
    PyObject_HEAD
    s_vpi_value  _vpi_value;      //struct vpi time.
} s_pyvpi_value, *p_pyvpi_value;

void pyvpi_value_Dealloc(p_pyvpi_value self);
int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds);
PyObject * pyvpi_value_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

//Get/Set Functions ......
//value
PyObject * s_pyvpi_value_getvalue(s_pyvpi_value *self, void *closure);
int        s_pyvpi_value_setvalue(s_pyvpi_value *self, PyObject *value, void *closure);

static PyMethodDef  pyvpi_value_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_value_members[]  = {
    {"format", T_UINT, offsetof(s_pyvpi_value, _vpi_value.format), 0, " format"},
    {NULL}
};
static PyGetSetDef pyvpi_value_getsets[]  = {
    {"value", (getter)s_pyvpi_value_getvalue, 
    (setter)s_pyvpi_value_setvalue,"get/set value.",NULL},
    {NULL}
};
static PyTypeObject pyvpi_value_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.Value",             /*tp_name*/
    sizeof(s_pyvpi_value),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_value_Dealloc, /*tp_dealloc*/    
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
    "pyvpi value objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_value_methods,       /* tp_methods */
    pyvpi_value_members,       /* tp_members */
    pyvpi_value_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_value_Init,      /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_value_New,           /* tp_new */
};

#endif
