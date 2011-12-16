#ifndef __PYCBDATA_H__
#define __PYCBDATA_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyvalue.h"
//typedef struct t_cb_data
//{
//  PLI_INT32    reason;                        /* callback reason */
//  PLI_INT32    (*cb_rtn)(struct t_cb_data *); /* call routine */
//  vpiHandle    obj;                           /* trigger object */
//  p_vpi_time   time;                          /* callback time */
//  p_vpi_value  value;                         /* trigger object value */
//  PLI_INT32    index;                         /* index of the memory word or
//                                                 var select that changed */
//  PLI_BYTE8   *user_data;
//} s_cb_data, *p_cb_data;
/* ------------------------------------------------------------------------- */
//PyObject vpi time struct data.
typedef struct t_pyvpi_cbdata
{
    PyObject_HEAD
    s_cb_data  _vpi_cbdata;         //struct vpi time.
    PyObject *callback;             //callback object
    vpiHandle cb_h;
} s_pyvpi_cbdata, *p_pyvpi_cbdata;

//Method ...
void pyvpi_cbdata_Dealloc(p_pyvpi_cbdata self);
int  pyvpi_cbdata_Init(p_pyvpi_cbdata self, PyObject *args, PyObject *kwds);
PyObject * pyvpi_cbdata_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

//Get/Set Functions ......
//reason
PyObject * s_pyvpi_cbdata_getreason(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_setreason(s_pyvpi_cbdata *self, PyObject *value, void *closure);
//trigger object
PyObject * s_pyvpi_cbdata_gettrgobj(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_settrgobj(s_pyvpi_cbdata *self, PyObject *value, void *closure);
//trigger time
PyObject * s_pyvpi_cbdata_gettime(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_settime(s_pyvpi_cbdata *self, PyObject *value, void *closure);
//trigger value
PyObject * s_pyvpi_cbdata_getvalue(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_setvalue(s_pyvpi_cbdata *self, PyObject *value, void *closure);
//index
PyObject * s_pyvpi_cbdata_getindex(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_setindex(s_pyvpi_cbdata *self, PyObject *value, void *closure);
//callback
PyObject * s_pyvpi_cbdata_getcallback(s_pyvpi_cbdata *self, void *closure);
int        s_pyvpi_cbdata_setcallback(s_pyvpi_cbdata *self, PyObject *value, void *closure);

/* _pyvpi_cb_rtn(p_cb_data) :
 * Function for callback.
 */
PLI_INT32 _pyvpi_cb_rtn(p_cb_data data);

static PyMethodDef  pyvpi_cbdata_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_cbdata_members[]  = {
    {"cb_h", T_ULONG, offsetof(s_pyvpi_cbdata, cb_h), READONLY, "callback handle" },
    {NULL}
};
static PyGetSetDef pyvpi_cbdata_getsets[]  = {
    {"reason", (getter)s_pyvpi_cbdata_getreason, 
    (setter)s_pyvpi_cbdata_setreason,"set callback reason.",NULL},
    {"trgobj", (getter)s_pyvpi_cbdata_gettrgobj, 
    (setter)s_pyvpi_cbdata_settrgobj,"set trigger object.",NULL},
    {"time", (getter)s_pyvpi_cbdata_gettime, 
    (setter)s_pyvpi_cbdata_settime,"set trigger time.",NULL},
    {"value", (getter)s_pyvpi_cbdata_getvalue, 
    (setter)s_pyvpi_cbdata_setvalue,"set trigger value.",NULL},
    {"index", (getter)s_pyvpi_cbdata_getindex, 
    (setter)s_pyvpi_cbdata_setindex,"set index.",NULL},
    {"callback", (getter)s_pyvpi_cbdata_getcallback, 
    (setter)s_pyvpi_cbdata_setcallback,"set callback for trigger.",NULL},
    {NULL}
};

static PyTypeObject pyvpi_cbdata_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi.cbData",            /*tp_name*/
    sizeof(s_pyvpi_cbdata),    /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_cbdata_Dealloc, /*tp_dealloc*/    
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
    "pyvpi cbdata objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_cbdata_methods,      /* tp_methods */
    pyvpi_cbdata_members,      /* tp_members */
    pyvpi_cbdata_getsets,      /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_cbdata_Init,      /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_cbdata_New,           /* tp_new */
};

#endif
