#ifndef __PYDELAY_H__
#define __PYDELAY_H__
#include "Python.h"
#include "structmember.h"

#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"
#include "pytime.h"
#include "pyhandle.h"

//typedef struct t_vpi_delay
//{
//  struct t_vpi_time *da;         /* pointer to user allocated array of
//                                    delay values */
//  PLI_INT32 no_of_delays;        /* number of delays */
//  PLI_INT32 time_type;           /* [vpiScaledRealTime, vpiSimTime,
//                                     vpiSuppressTime] */
//  PLI_INT32 mtm_flag;            /* true for mtm values */
//  PLI_INT32 append_flag;         /* true for append */
//  PLI_INT32 pulsere_flag;        /* true for pulsere values */
//} s_vpi_delay, *p_vpi_delay;

/*****************************************************************************
 * PyObject vpi delay struct data.
 * For the strange vpi delays struct, we keep two time array, one for pdelays
 * and the other for _vpi_delay.da ;
 *****************************************************************************/
typedef struct t_pyvpi_delays
{
    PyObject_HEAD
    s_vpi_delay  _vpi_delay;      //struct vpi delay.
    PyObject*    pdelays;
} s_pyvpi_delays, *p_pyvpi_delays;

extern void pyvpi_delays_Dealloc(p_pyvpi_delays self);
extern int  pyvpi_delays_Init(s_pyvpi_delays *self, PyObject *args, PyObject *kwds);
extern PyObject * pyvpi_delays_New(PyTypeObject *type, PyObject *args, PyObject *kwds);

//Get/Set Functions ......
//delays
PyObject * s_pyvpi_delays_getdelays(s_pyvpi_delays *self, void *closure);
int        s_pyvpi_delays_setdelays(s_pyvpi_delays *self, PyObject *value, void *closure);

static PyMethodDef  pyvpi_delays_methods[] = {
    {NULL}
};
static PyMemberDef pyvpi_delays_members[]  = {
//    {"no_of_delays",    T_INT,  offsetof(s_pyvpi_delays, _vpi_delay.no_of_delays),   0, "number of delays"},
    {"time_type",       T_INT,  offsetof(s_pyvpi_delays, _vpi_delay.time_type),      0, "[vpiScaledRealTime, vpiSimTime,vpiSuppressTime]"},
    {"mtm_flag",        T_INT,  offsetof(s_pyvpi_delays, _vpi_delay.mtm_flag),       0, "true for mtm values"},
    {"append_flag",     T_INT,  offsetof(s_pyvpi_delays, _vpi_delay.append_flag),    0, "true for append"},
    {"pulsere_flag",    T_INT,  offsetof(s_pyvpi_delays, _vpi_delay.pulsere_flag),   0, "true for pulsere values"},
    {NULL}
};
static PyGetSetDef pyvpi_delays_getsets[]  = {
    {"delays", (getter)s_pyvpi_delays_getdelays, 
    (setter)s_pyvpi_delays_setdelays,"get/set delays.",NULL},
    {NULL}
};
#endif
