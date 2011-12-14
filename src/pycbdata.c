#include "pycbdata.h"

void pyvpi_cbdata_Dealloc(p_pyvpi_cbdata self)
{
     //Free self.
    self->ob_type->tp_free((PyObject*)self);
}
/*
 * CbData initial,
 * params : 
 *      reason  = ? (PLI_INT32)
 *      trg_obj = ? (vpiHandle)
 *      cb_time = ? (PyObject * pyvpi.Time)
 */
int  pyvpi_cbdata_Init(p_pyvpi_cbdata self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"reason","trgobj","time","value","index", NULL};    
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|il", kwlist,
                                      &self->_vpi_cbdata.reason,
                                      &self->_vpi_cbdata.obj))
        return -1;
    self->_vpi_cbdata.cb_rtn = _pyvpi_cb_rtn;  //All CbObject's callback is _pyvpi_cb_rtn
    vpi_printf("cb is initial...%x\n",_pyvpi_cb_rtn);
    return 0;
}

PyObject * pyvpi_cbdata_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    p_pyvpi_cbdata   self;
    self = (p_pyvpi_cbdata)type->tp_alloc(type, 0);
    return (PyObject *) self;
}

//Get/Set Functions
//reason
PyObject * s_pyvpi_cbdata_getreason(s_pyvpi_cbdata *self, void *closure)
{
    return Py_BuildValue("i", self->_vpi_cbdata.reason);
}
int        s_pyvpi_cbdata_setreason(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set reason to NULL.");
        return -1;
    }

    if (! PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The reason must be a int.");
        return -1;
    }
    self->_vpi_cbdata.reason = PyInt_AS_LONG(value);
    return 0;
}
//trigger object
PyObject * s_pyvpi_cbdata_gettrgobj(s_pyvpi_cbdata *self, void *closure)
{
    return Py_BuildValue("l", self->_vpi_cbdata.obj);
}
int        s_pyvpi_cbdata_settrgobj(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set trigger object to NULL.");
        return -1;
    }

    if (! PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The reason trigger object be a long.");
        return -1;
    }
    self->_vpi_cbdata.obj = (vpiHandle)PyLong_AsLong(value);
    return 0;
}
//trigger time
PyObject * s_pyvpi_cbdata_gettime(s_pyvpi_cbdata *self, void *closure)
{
    return NULL;
}
int        s_pyvpi_cbdata_settime(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    return -1;
}
//trigger value
PyObject * s_pyvpi_cbdata_getvalue(s_pyvpi_cbdata *self, void *closure)
{
    return NULL;
}
int        s_pyvpi_cbdata_setvalue(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    return -1;
}
//index
PyObject * s_pyvpi_cbdata_getindex(s_pyvpi_cbdata *self, void *closure)
{
    return Py_BuildValue("i", self->_vpi_cbdata.index);
}
int        s_pyvpi_cbdata_setindex(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set index to NULL.");
        return -1;
    }

    if (! PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The index must be a int.");
        return -1;
    }
    self->_vpi_cbdata.index = PyInt_AS_LONG(value);
    return 0;
}
//callback
PyObject * s_pyvpi_cbdata_getcallback(s_pyvpi_cbdata *self, void *closure)
{   
    if(self->callback == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    else {
        return self->callback;
    }
}

int        s_pyvpi_cbdata_setcallback(s_pyvpi_cbdata *self, PyObject *value, void *closure){
    if (!PyCallable_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "Parameter must be callable.");
            return -1;
        }
    Py_XINCREF(value);
    self->callback = value;
    return 0;
}
/* _pyvpi_cb_rtn(p_cb_data) :
 * Function for callback.
 */
PLI_INT32 _pyvpi_cb_rtn(p_cb_data data)
{
    PyObject *arglist;
    vpi_printf("_pyvpi_cb_rtn is running.");
    //In this function, we must convert data to s_pyvpi_cbdata;
    p_pyvpi_cbdata self = (s_pyvpi_cbdata *) (data - offsetof(s_pyvpi_cbdata,_vpi_cbdata));
    //Return -1 if callback is not callback...
    if (!PyCallable_Check(self->callback)) return -1;    
    arglist = Py_BuildValue("(O)",self);
    (void) PyObject_CallObject(self->callback, arglist);
    Py_DECREF(arglist);
    return 0;
}
