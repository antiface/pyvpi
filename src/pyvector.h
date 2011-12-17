#ifndef __PYVECTOR_H__
#define __PYVECTOR_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"
//typedef struct t_vpi_vecval
//{
//  /* following fields are repeated enough times to contain vector */
//  PLI_UINT32 aval, bval;          /* bit encoding: ab: 00=0, 10=1, 11=X, 01=Z */
//} s_vpi_vecval, *p_vpi_vecval;
/* ------------------------------------------------------------------------- */
//PyObject vpi vector struct data.
typedef struct t_pyvpi_vector
{
    PyObject_HEAD
    s_vpi_vecval  *_vpi_vector;      //struct vpi vector point.
} s_pyvpi_vector, *p_pyvpi_vector;

void pyvpi_vector_Dealloc(p_pyvpi_vector self);
int  pyvpi_vector_Init(s_pyvpi_vector *self, PyObject *args, PyObject *kwds);
PyObject * pyvpi_vector_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

static PyMethodDef  pyvpi_vector_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_vector_members[]  = {
    {NULL}
};
static PyGetSetDef pyvpi_vector_getsets[]  = {
    {NULL}
};
#endif
