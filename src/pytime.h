#ifndef __PYTIME_H__
#define __PYTIME_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"
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

extern void pyvpi_time_Dealloc(p_pyvpi_time self);
extern int  pyvpi_time_Init(s_pyvpi_time *self, PyObject *args, PyObject *kwds);
extern PyObject * pyvpi_time_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

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
#endif
