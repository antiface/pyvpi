#include "pycbdata.h"
//Type define here.
PyTypeObject pyvpi_cbdata_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._cbData",            /*tp_name*/
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

void pyvpi_cbdata_Dealloc(p_pyvpi_cbdata self)
{
    //Free self.
    p_pyvpi_value pvalue;
    p_pyvpi_time  ptime;
    pvalue = (p_pyvpi_value) ((size_t)self->_vpi_cbdata.value - offsetof(s_pyvpi_value, _vpi_value));
    Py_DECREF(pvalue);
    ptime  = (p_pyvpi_time)  ((size_t)self->_vpi_cbdata.time - offsetof(s_pyvpi_time, _vpi_time));
    Py_DECREF(ptime);
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._cbData is release,ptr is 0x%x.\n",self);
#endif
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
    //TBD, add pyvpi_Value, etc...
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|il", kwlist,
                                      &self->_vpi_cbdata.reason,
                                      &self->_vpi_cbdata.obj))
        return -1;
    self->_vpi_cbdata.cb_rtn = _pyvpi_cb_rtn;  //All CbObject's callback is _pyvpi_cb_rtn.
    self->_vpi_cbdata.user_data = (PLI_BYTE8 *) self;   //The user_data always be self.        
    return 0;
}

PyObject * pyvpi_cbdata_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    p_pyvpi_cbdata   self;
    p_pyvpi_value    pvalue;
    p_pyvpi_time     ptime;
    
    self = (p_pyvpi_cbdata)type->tp_alloc(type, 0);
    if(!self){
        PyErr_SetString(PyExc_TypeError, "Can't allocate a pyvpi._cbData memory.");
        return NULL;
    }
    
    pvalue = (p_pyvpi_value) pyvpi_value_New(&pyvpi_value_Type,PyTuple_New(0),PyDict_New());
    pyvpi_value_Init(pvalue,PyTuple_New(0),PyDict_New());
    if(!pvalue){
        PyErr_SetString(PyExc_TypeError, "Can't new a pyvpi._Value object.");
        return NULL;
    }
    
    //Py_INCREF(pvalue);  //Add reference for value. <Don't add pvalue reference.>
    self->_vpi_cbdata.value = &pvalue->_vpi_value;

    ptime = (p_pyvpi_time) pyvpi_time_New(&pyvpi_time_Type,PyTuple_New(0),PyDict_New());
    pyvpi_time_Init(ptime,PyTuple_New(0),PyDict_New());
    if(!ptime){
        PyErr_SetString(PyExc_TypeError, "Can't new a pyvpi._Time object.");
        return NULL;
    }
    self->_vpi_cbdata.time = &ptime->_vpi_time;
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi_cbdata is allocate,ptr is <0x%x>, type ptr is <0x%x>.\n",self,type);
#endif
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
        PyErr_SetString(PyExc_TypeError, "Can't set reason to NULL.");
        return -1;
    }

    if (! PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The reason must be an int.");
        return -1;
    }
    self->_vpi_cbdata.reason = PyInt_AS_LONG(value);
    return 0;
}
//trigger object
PyObject * s_pyvpi_cbdata_gettrgobj(s_pyvpi_cbdata *self, void *closure)
{
    return Py_BuildValue("K", self->_vpi_cbdata.obj);
}

int        s_pyvpi_cbdata_settrgobj(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Can't set trigger object to NULL.");
        return -1;
    }
    if (! PyLong_Check(value)) {
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
    p_pyvpi_time ptime;
    ptime  = (p_pyvpi_time)  ((size_t)self->_vpi_cbdata.time - offsetof(s_pyvpi_time, _vpi_time));
    Py_INCREF(ptime);
    return (PyObject *) ptime;
}
int        s_pyvpi_cbdata_settime(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    p_pyvpi_time ptime, tmp = (p_pyvpi_time) value;
    ptime  = (p_pyvpi_time)  ((size_t)self->_vpi_cbdata.time - offsetof(s_pyvpi_time, _vpi_time));
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Can't set time object to NULL.");
        return -1;
    }
    if (! PyObject_TypeCheck(value,&pyvpi_time_Type)) {
        PyErr_SetString(PyExc_TypeError,
                        "The value object be a pyvpi._Time.");
        return -1;
    }
    Py_DECREF(ptime);
    Py_INCREF(tmp);
    self->_vpi_cbdata.time = &tmp->_vpi_time;
    return 0;
}
//value
PyObject * s_pyvpi_cbdata_getvalue(s_pyvpi_cbdata *self, void *closure)
{
    p_pyvpi_value pvalue ;
    pvalue = (p_pyvpi_value) ((size_t)self->_vpi_cbdata.value - offsetof(s_pyvpi_value, _vpi_value));
    Py_INCREF(pvalue);
    return (PyObject *) pvalue;
}

int        s_pyvpi_cbdata_setvalue(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    p_pyvpi_value pvalue, tmp = (p_pyvpi_value) value;
    pvalue = (p_pyvpi_value) ((size_t)self->_vpi_cbdata.value - offsetof(s_pyvpi_value, _vpi_value));
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Can't set value object to NULL.");
        return -1;
    }
    if (! PyObject_TypeCheck(value,&pyvpi_value_Type)) {
        PyErr_SetString(PyExc_TypeError,
                        "The value object be a pyvpi._Value.");
        return -1;
    }
    Py_DECREF(pvalue);
    Py_INCREF(tmp);
    self->_vpi_cbdata.value = &tmp->_vpi_value;
    return 0;
}
//index
PyObject * s_pyvpi_cbdata_getindex(s_pyvpi_cbdata *self, void *closure)
{
    return Py_BuildValue("i", self->_vpi_cbdata.index);
}
int        s_pyvpi_cbdata_setindex(s_pyvpi_cbdata *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Can't set index to NULL.");
        return -1;
    }

    if (! PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The index must be an int.");
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
            PyErr_SetString(PyExc_TypeError, "Parameter must be a callable.");
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
    int      blen = 0,nd_alloc = 0;
    //In this function, we must convert data to s_pyvpi_cbdata;
    p_pyvpi_cbdata self = (s_pyvpi_cbdata *) data->user_data;
    p_pyvpi_value  pv   = (p_pyvpi_value) ((size_t)self->_vpi_cbdata.value - offsetof(s_pyvpi_value, _vpi_value));
    //Return -1 if callback is not callback...
    if (!PyCallable_Check(self->callback)) return -1;
    
    //1. We must copy the tmp value to our struct...    
    //First, Check bit length if the value format is vpiVectorVal.
    if(data->value->format == vpiVectorVal) {
        blen = vpi_get(vpiSize,data->obj);
        pyvpi_CheckError();   //TBD Strange here...
        pv->vec_size  = blen;
    }
    
    if(blen < 0) blen = 0; //???Need or not TBD
    //Second , Check need allocate space or not?
    if(blen/32 + 1 > pv->cache_size) {
        nd_alloc = pv->cache_size * 2;        
    }
    if(data->value->format == vpiStringVal || 
       data->value->format == vpiBinStrVal ||
       data->value->format == vpiOctStrVal ||
       data->value->format == vpiDecStrVal ||
       data->value->format == vpiHexStrVal)
    {
        if(strlen(data->value->value.str) > (pv->cache_size - 1))
            nd_alloc = pv->cache_size * 2;
    }
#ifdef PYVPI_DEBUG
    if(nd_alloc) {
        vpi_printf("[PYVPI_DEBUG] _pyvpi_cb_rtn  need alloc new memory, blen is 0x%x, nd_alloc is 0x%x.\n",blen,nd_alloc);
    }
#endif
    copy_vpi_value(self->_vpi_cbdata.value,data->value,blen,nd_alloc);
    
    if(nd_alloc) {
        switch(pv->_vpi_value.format){
            case vpiBinStrVal: 
            case vpiOctStrVal: 
            case vpiDecStrVal:
            case vpiHexStrVal: 
            case vpiStringVal:
                pv->cache_ptr = (void *) pv->_vpi_value.value.str;
            case vpiVectorVal:                
                pv->cache_ptr = (void *) pv->_vpi_value.value.vector;
            default : 
                return -1;
        }        
    }
    
    //2. We must copy the tmp time to our struct...
    *(self->_vpi_cbdata.time) = *(data->time);    
    arglist = Py_BuildValue("(O)",self);
    (void) PyObject_CallObject(self->callback, arglist);
    Py_DECREF(arglist);
    return 0;
}
