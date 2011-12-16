#ifndef __PYVALUE_H__
#define __PYVALUE_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"
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
    PLI_UINT32   vec_size;        //vector size.
    PLI_UINT32   cache_size;      //Cache size, used to store vector/string/strength/misc/time
    void*        cache_ptr;
} s_pyvpi_value, *p_pyvpi_value;

extern void pyvpi_value_Dealloc(p_pyvpi_value self);
extern int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds);
extern PyObject * pyvpi_value_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

//misc
extern void copy_vpi_value(s_vpi_value *nvalp, s_vpi_value *ovalp, PLI_INT32 blen, PLI_INT32 nd_alloc);

//Get/Set Functions ......
//value
PyObject * s_pyvpi_value_getvalue(s_pyvpi_value *self, void *closure);
int        s_pyvpi_value_setvalue(s_pyvpi_value *self, PyObject *value, void *closure);

static PyMethodDef  pyvpi_value_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_value_members[]  = {
    {"format",  T_UINT, offsetof(s_pyvpi_value, _vpi_value.format), 0, " format"},
    {"vec_size", T_UINT, offsetof(s_pyvpi_value, vec_size), READONLY,  " vector size"},
    {NULL}
};
static PyGetSetDef pyvpi_value_getsets[]  = {
    {"value", (getter)s_pyvpi_value_getvalue, 
    (setter)s_pyvpi_value_setvalue,"get/set value.",NULL},
    {NULL}
};

#endif
