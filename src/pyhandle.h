#ifndef __PYHANDLE_H__
#define __PYHANDLE_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"
/* ------------------------------------------------------------------------- */
//PyObject vpi time struct data.
//PyObject vpi time struct data.
typedef struct t_pyvpi_handle
{
    PyObject_HEAD
    vpiHandle  _vpi_handle;      //vpiHandle
} s_pyvpi_handle, *p_pyvpi_handle;

extern void pyvpi_handle_Dealloc(p_pyvpi_handle self);
extern int  pyvpi_handle_Init(s_pyvpi_handle *self, PyObject *args, PyObject *kwds);
extern PyObject * pyvpi_handle_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

static PyMethodDef  pyvpi_handle_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_handle_members[]  = {
    {NULL}
};
static PyGetSetDef pyvpi_handle_getsets[]  = {
    {NULL}
};
#endif

