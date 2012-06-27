#include "pyvpi.h"
#include <io.h>

/*****************************************************************************
 * This is all code for python.
/*****************************************************************************/
//We Define two errors, if vpi call function is error, VpiError will be assert,
//else if python error, PyError will be set.
/*****************************************************************************
 * pyvpi_CheckError()
 * Checks if an error was reported by the last vpi function called
 * and, if so, set VpiError and return error code.
 *****************************************************************************/
int 
pyvpi_CheckError( void )
{
    int              error_code;
    s_vpi_error_info error_info;

    error_code = vpi_chk_error( &error_info );
    if ( error_code && error_info.message ) {
        PyErr_SetString(VpiError,  error_info.message);
    }
    return error_code;
}

static int 
CheckError( void )
{
    int              error_code;
    s_vpi_error_info error_info;

    error_code = vpi_chk_error( &error_info );
    if ( error_code && error_info.message ) {
        vpi_printf("%s\n",error_info.message);
    }
    return error_code;
}

static PyObject* 
pyvpi_Print(PyObject *self, PyObject *args)
{
    PLI_BYTE8 *str;
    if (!PyArg_ParseTuple(args, "s", &str))
    {
        PyErr_SetString(VpiError,  "Error args, must be (str).");
        return NULL;
    }
    vpi_printf("%s",str);
    Py_INCREF(Py_None);
    return Py_None;
}

/* for obtaining handles */
/*****************************************************************************
 * pyvpi_HandleByName()
 * XXTERN vpiHandle  vpi_handle_by_name  PROTO_PARAMS((PLI_BYTE8 *name,
 *                                                     vpiHandle scope));
 *****************************************************************************/
static PyObject* 
pyvpi_HandleByName(PyObject *self, PyObject *args)
{
    PLI_BYTE8 *name;
    p_pyvpi_handle scope = (p_pyvpi_handle)Py_None,oans;
    vpiHandle ans;
    if (!PyArg_ParseTuple(args, "s|O", &name,&scope))
    {
        PyErr_SetString(VpiError,  "Error args, must be (str,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(scope,&pyvpi_handle_Type)) {
        pyvpi_debug(sprintf(print_buffer, "handleByName 's 2nd arg is "
                    "not pyvpi.Handle type, trade scope as NULL.\n"));
        ans = vpi_handle_by_name(name, NULL);
    }
    else {
        ans = vpi_handle_by_name(name,scope->_vpi_handle);
    }
    if(pyvpi_CheckError())
       return NULL;

    if(ans == NULL) {
        PyErr_Format(VpiError,  "Can't get right handle by name :\"%s\"!", name);
        return NULL;
    }
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans;
}
/* 
 * XXTERN vpiHandle  vpi_handle_by_index PROTO_PARAMS((vpiHandle object,
 *                                                     PLI_INT32 indx));
 */
static PyObject* 
pyvpi_HandleByIndex(PyObject *self, PyObject *args)
{
    p_pyvpi_handle object,oans;
    PLI_INT32 indx;
    vpiHandle ans;
    if (!PyArg_ParseTuple(args, "Ok", &object,&indx))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle,long).");
        return NULL;
    }
    if (!PyObject_TypeCheck(object,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle,long).");
        return NULL;
    }
    else {
        ans = vpi_handle_by_index(object->_vpi_handle,indx);
    }
    if(pyvpi_CheckError())
       return NULL;
    if(ans == NULL) {
        PyErr_Format(VpiError,  "Can't get right handle by index : %d.", indx);
        return NULL;
    }
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans;  
}

/* for traversing relationships */
/*
    XXTERN vpiHandle  vpi_handle          PROTO_PARAMS((PLI_INT32 type,
                                                        vpiHandle refHandle));
*/
static PyObject* 
pyvpi_Handle(PyObject *self, PyObject *args)
{
    p_pyvpi_handle refHandle,oans;
    PLI_INT32 type;
    vpiHandle ans;   
    if (!PyArg_ParseTuple(args, "iO", &type,&refHandle))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(refHandle,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (long,pyvpi.Handle).");
        return NULL;    // TBD
    }
    else {
        ans = vpi_handle(type,refHandle->_vpi_handle);
    }
    if(pyvpi_CheckError())
       return NULL;
    if(ans == NULL) {
        PyErr_Format(VpiError,  "There is not relation between %d and <%lx>.",
            type, refHandle);
        return NULL;
    }
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans;   
}
/*
    XXTERN vpiHandle  vpi_handle_multi    PROTO_PARAMS((PLI_INT32 type,
                                                        vpiHandle refHandle1,
                                                        vpiHandle refHandle2,
                                                        ... ));
*/
//Can port this function now, this will be changed in future.
/*
    XXTERN vpiHandle  vpi_iterate         PROTO_PARAMS((PLI_INT32 type,
                                                        vpiHandle refHandle));
*/
static PyObject* 
pyvpi_Iterate(PyObject *self, PyObject *args)
{
    PLI_INT32 type;
    p_pyvpi_handle refHandle,oans;
    vpiHandle ans;
    if (!PyArg_ParseTuple(args, "iO", &type,&refHandle))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(refHandle, &pyvpi_handle_Type)) {
        pyvpi_trace(sprintf(print_buffer, "iterate 's 2nd arg is "
                    "not pyvpi.Handle type, trade refHandle as NULL.\n"));
        ans = vpi_iterate(type, NULL);
    }
    else {
        ans = vpi_iterate(type,refHandle->_vpi_handle);
    }

    if(pyvpi_CheckError())
       return NULL;

    if(ans == NULL) {
        PyErr_Format(VpiError,  "Can't get right iterator in handle: <%lx>.",
            refHandle);
        return NULL;
    }

    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans;   
}

/* 
    XXTERN vpiHandle  vpi_scan            PROTO_PARAMS((vpiHandle iterator));
*/
static PyObject* 
pyvpi_Scan(PyObject *self, PyObject *args)
{
    p_pyvpi_handle iterator,oans;
    vpiHandle ans;
    if (!PyArg_ParseTuple(args, "O", &iterator))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(iterator,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle).");
        return NULL;
    }

    ans = vpi_scan(iterator->_vpi_handle);
    if(pyvpi_CheckError())
        return NULL;
    if(ans != NULL) {
        oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    }
    else {
        pyvpi_verbose(sprintf(print_buffer, "pyvpi.Handle->Handle is "
                    "release,ptr is <0x%lx>.\n", iterator->_vpi_handle));
        iterator->is_free = 1;
        Py_INCREF(Py_None);
        return Py_None;
    }
    return (PyObject *)oans;   
}

/* for processing properties */
/*
    XXTERN PLI_INT32  vpi_get             PROTO_PARAMS((PLI_INT32 property,
                                                        vpiHandle object));
    
    XXTERN PLI_INT64  vpi_get64           PROTO_PARAMS((PLI_INT32 property,
                                                        vpiHandle object));
    XXTERN PLI_BYTE8 *vpi_get_str         PROTO_PARAMS((PLI_INT32 property,
                                                        vpiHandle object));
*/
static PyObject* 
pyvpi_Get(PyObject *self, PyObject *args)
{
    PLI_INT32 property;
    p_pyvpi_handle object;
    PLI_INT32 ans;
    if (!PyArg_ParseTuple(args, "iO", &property,&object))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(object,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL; //TBD
    }

    ans = vpi_get(property,object->_vpi_handle);
    if(pyvpi_CheckError())
       return NULL;
    return Py_BuildValue("I", ans);
}

static PyObject* 
pyvpi_Get64(PyObject *self, PyObject *args)
{
    PLI_INT32 property;
    p_pyvpi_handle object;
    PLI_INT64 ans;
    if (!PyArg_ParseTuple(args, "iO", &property,&object))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(object,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL; //TBD
    }

    ans = vpi_get(property,object->_vpi_handle);
    if(pyvpi_CheckError())
       return NULL;        
    return Py_BuildValue("I", ans);
}

static PyObject* 
pyvpi_GetStr(PyObject *self, PyObject *args)
{
    PLI_INT32 property;
    p_pyvpi_handle object;
    char  *ans;
    if (!PyArg_ParseTuple(args, "iO", &property,&object))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(object,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (int,pyvpi.Handle).");
        return NULL; //TBD
    }

    ans = vpi_get_str(property,object->_vpi_handle);
    if(pyvpi_CheckError())
       return NULL;
    return Py_BuildValue("s", ans);
}

/*
    vpiHandle  vpi_register_cb     (p_cb_data cb_data_p);
    PLI_INT32  vpi_remove_cb       (vpiHandle cb_obj);
    void       vpi_get_cb_info     (vpiHandle object, p_cb_data cb_data_p);
    vpiHandle  vpi_register_systf  (p_vpi_systf_data   systf_data_p);
    void       vpi_get_systf_info  (vpiHandle object, p_vpi_systf_data   systf_data_p);
*/
static PyObject* 
pyvpi_RegisterCb(PyObject *self, PyObject *args) 
{                                                                  //the args of vpi_remove_cb and vpi_get_cb_info.
    p_pyvpi_cbdata  cbdata;
    vpiHandle  ans;
    p_pyvpi_handle oans; 
    if (!PyArg_ParseTuple(args, "O", &cbdata))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.CbData).");
        return NULL;
    }
    Py_INCREF(cbdata);    /* Must incref the cb information */
    ans = vpi_register_cb(&cbdata->_vpi_cbdata);
    if(pyvpi_CheckError())
        return NULL;
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    Py_DECREF(cbdata->cb_h);
    cbdata->cb_h =  (PyObject *)oans;
    Py_INCREF(oans);
    return (PyObject *)oans;   
}

static PyObject* 
pyvpi_RemoveCb(PyObject *self, PyObject *args)
{
    p_pyvpi_cbdata  cbdata;
    p_pyvpi_handle  cbhandle;
    PLI_INT32  ans;
    if (!PyArg_ParseTuple(args, "O", &cbdata))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.CbData).");
        return NULL;
    }

    if (PyObject_TypeCheck(cbdata,&pyvpi_cbdata_Type)) {
        cbhandle = (p_pyvpi_handle) cbdata->cb_h;
    }
    else {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.CbData).");
        return NULL;
    }
    ans = vpi_remove_cb(cbhandle->_vpi_handle);
    if(pyvpi_CheckError())
        return NULL;
    cbhandle->is_free = 1;
    pyvpi_verbose(sprintf(print_buffer, "pyvpi.Handle->Handle is "
                    "release,ptr is <0x%lx>.\n", cbhandle->_vpi_handle));
    Py_DECREF(cbdata);    /* Remove cbdata reference! */      
    return Py_BuildValue("i", ans);
}

static PyObject* 
pyvpi_GetCbInfo(PyObject *self, PyObject *args)
{
     //There is no use to port this function;
     //TBD
    pyvpi_warning(sprintf(print_buffer,"pyvpi.getCbInfo is not allowed "
                "used in this version!\n"));
    Py_INCREF(Py_None);
    return Py_None;
//# p_pyvpi_handle  object,trgobj;
//# p_pyvpi_cbdata  cbdata;
//# PyObject*       pdict = PyDict_New();
//# PyObject*       ptpl = PyTuple_New(0);
//# if (!PyArg_ParseTuple(args, "O", &object))
//# {
//#     PyErr_SetString(VpiError,  "Error args, must be (pyvpi._vpiHandle).");
//#     return NULL;
//# }
//# //Initial cbdata;
//# cbdata = (p_pyvpi_cbdata) pyvpi_cbdata_New(&pyvpi_cbdata_Type,ptpl,pdict);
//# vpi_get_cb_info(object->_vpi_handle,&cbdata->_vpi_cbdata);
//# // Add trgobj info.    
//# trgobj = (p_pyvpi_handle) _pyvpi_handle_New(cbdata->_vpi_cbdata.obj);
//# //Initial cbData...
//# PyDict_SetItemString(pdict,"trgobj",(PyObject*) trgobj);
//# Py_DECREF(trgobj);
//# pyvpi_cbdata_Init(cbdata,ptpl,pdict);    
//# Py_DECREF(ptpl);
//# Py_DECREF(pdict);
//# if(pyvpi_CheckError())
//#    return NULL;
//# return (PyObject*) cbdata;
 }

static PyObject*
pyvpi_RegisterSysTf(PyObject *self, PyObject *args) 
{
    s_pyvpi_systfdata*  systfdata;
    vpiHandle  ans;
    if (!PyArg_ParseTuple(args, "O", &systfdata))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.SysTfData).");
        return NULL;
    }
    ans = vpi_register_systf(&systfdata->_vpi_systfdata);
    if(pyvpi_CheckError())
       return NULL;
    Py_INCREF(systfdata); //Always increment systfdata.
    Py_INCREF(Py_None);
    return (PyObject *)Py_None;
}

static PyObject* 
pyvpi_GetSysTfInfo(PyObject *self, PyObject *args)
{
    //There is no use to port this function;
    pyvpi_warning(sprintf(print_buffer,"pyvpi.getSysTfInfo is not allowed "
                 "used in this version!\n"));
    Py_INCREF(Py_None);
    return Py_None;
}

/* value processing
void       vpi_get_value       PROTO_PARAMS((vpiHandle expr,
                                             p_vpi_value value_p));
vpiHandle  vpi_put_value       PROTO_PARAMS((vpiHandle object,
                                             p_vpi_value value_p,
                                             p_vpi_time time_p,
                                             PLI_INT32 flags));
void       vpi_get_value_array PROTO_PARAMS((vpiHandle object,
                                             p_vpi_arrayvalue arrayvalue_p,
                                             PLI_INT32 *index_p,
                                             PLI_UINT32 num));
void       vpi_put_value_array PROTO_PARAMS((vpiHandle object,
                                             p_vpi_arrayvalue arrayvalue_p,
                                             PLI_INT32 *index_p,
                                             PLI_UINT32 num));    
*/
static PyObject * 
pyvpi_PutValue(PyObject *self, PyObject *args)
{
    p_pyvpi_handle  handle,oans; 
    p_pyvpi_value   value;
    p_pyvpi_time    time = (p_pyvpi_time) Py_None;
    PLI_INT32       flags = vpiNoDelay;
    vpiHandle       ans;
    if (!PyArg_ParseTuple(args, "OO|Oi", &handle, &value, &time, flags))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle,pyvpi.Value).");
        return NULL;
    }
    if(Py_TYPE(handle) != &pyvpi_handle_Type) {    
        PyErr_SetString(VpiError,  "Error args, 1st arg must be pyvpi.Handle.");
        return NULL;
    }
    if(Py_TYPE(value) != &pyvpi_value_Type) {
        pyvpi_debug(sprintf(print_buffer, "2nd arg of putValue is not pyvpi.Vaule, "
                    "trade it as NULL"));
        value = NULL;
    }
    if(Py_TYPE(time) != &pyvpi_time_Type) {    
        //PyErr_SetString(VpiError,  "Error args, 3nd arg must be pyvpi.Time.");
        //return NULL;
        pyvpi_debug(sprintf(print_buffer, "3nd arg of putValue is not pyvpi.Time, "
                    "trade it as NULL"));
        time = NULL;
    }
    ans = vpi_put_value(handle->_vpi_handle,
        value == NULL? NULL : &value->_vpi_value,
        time  == NULL? NULL : &time->_vpi_time,
        flags);
    if(pyvpi_CheckError())
        return NULL;
    if(ans == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans; 
}

static PyObject *
pyvpi_GetValue(PyObject *self, PyObject *args)
{
    /*  Describe :
     *  This function just update the fields of pyvpi.Value;
     * */
    p_pyvpi_handle  handle; 
    p_pyvpi_value   value;
    PLI_UINT32        blen;
    if (!PyArg_ParseTuple(args, "OO", &handle, &value))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle,pyvpi.Value).");
        return NULL;
    }
    if(Py_TYPE(handle) != &pyvpi_handle_Type) {    
        PyErr_SetString(VpiError,  "Error args, 1st arg must be pyvpi.Handle.");
        return NULL;
    }
    if(Py_TYPE(value) != &pyvpi_value_Type) {    
        PyErr_SetString(VpiError,  "Error args, 2nd arg must be pyvpi.Value.");
        return NULL;
    }
    if(value->_vpi_value.format == vpiVectorVal) {
        p_pyvpi_vector pvec;
        blen = vpi_get(vpiSize,handle->_vpi_handle);
        if(pyvpi_CheckError()){
            return NULL;
        }
        /* Update vetcotr cache to store the value.*/        
        pvec = (p_pyvpi_vector) value->obj;
        if(blen > pvec->size) {
            pvec->size = blen;
            pyvpi_vector_update_cache(pvec);
        }
    }
    vpi_get_value(handle->_vpi_handle,&value->_vpi_value);
    pyvip_value_update_value(value,&value->_vpi_value,blen);
    if(pyvpi_CheckError())
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
pyvpi_GetTime(PyObject *self, PyObject *args)
{
    p_pyvpi_handle  handle = (p_pyvpi_handle) Py_None;
    p_pyvpi_time    time = (p_pyvpi_time) Py_None;
    if (!PyArg_ParseTuple(args, "O|O", &time, &handle))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Time, pyvpi.Handle).");
        return NULL;
    }
    if(Py_TYPE(time) != &pyvpi_time_Type) {
        PyErr_SetString(VpiError,  "Error args, 1st arg must be pyvpi.Time.");
        return NULL;
    }
    if(Py_TYPE(handle) != &pyvpi_handle_Type) {
        vpi_get_time(0,&time->_vpi_time);
    }
    else 
    {        
        vpi_get_time(handle->_vpi_handle,&time->_vpi_time);
    }
    if(pyvpi_CheckError())
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* 
pyvpi_Control(PyObject *self, PyObject *args)
{
    PLI_INT32 op;
    if (!PyArg_ParseTuple(args, "k", &op))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int).");
        return NULL;
    }   
    return Py_BuildValue("i",vpi_control(op));    
}

static PyObject*
pyvpi_SetDebugLevel(PyObject *self, PyObject *args)
{
    PLI_INT32 new_level = PRINT_NOTE;
    if (!PyArg_ParseTuple(args, "k", &new_level))
    {
        PyErr_SetString(VpiError,  "Error args, must be (int).");
        return NULL;
    }
    print_level = new_level;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyvpi_Methods[] = {
   /* for obtaining handles */
   {"handleByName",    pyvpi_HandleByName,     METH_VARARGS,   "vpiHandle  vpi_handle_by_name (PLI_BYTE8 *name, vpiHandle scope)."},
   {"handleByIndex",   pyvpi_HandleByIndex,    METH_VARARGS,   "vpiHandle  pyvpi_HandleByIndex (vpiHandle object, PLI_INT32 indx)."},
   /* for traversing relationships */
   {"handle",          pyvpi_Handle,           METH_VARARGS,   "vpiHandle  vpi_handle   (PLI_INT32 type, vpiHandle refHandle)"},
   //{"HandleMulti",     pyvpi_HandleMulti,      METH_VARARGS,   "vpiHandle  vpi_handle_multi    (PLI_INT32 type, vpiHandle refHandle1, vpiHandle refHandle2, ... )"},
   {"iterate",         pyvpi_Iterate,          METH_VARARGS,   "vpiHandle  vpi_iterate (PLI_INT32 type, vpiHandle refHandle)"},
   {"scan",            pyvpi_Scan,             METH_VARARGS,   "vpiHandle  vpi_scan    (vpiHandle iterator)"},
   /* for processing data*/
   {"getValue",        pyvpi_GetValue,         METH_VARARGS,   "void       vpi_get_value       (vpiHandle expr, p_vpi_value value_p)."},
   {"putValue",        pyvpi_PutValue,         METH_VARARGS,   "vpiHandle  vpi_put_value       (vpiHandle expr, p_vpi_value value_p, p_vpi_time time_p, PLI_INT32 flags)."},
   /* for processing properties */
   {"get",             pyvpi_Get,              METH_VARARGS,   "PLI_INT32  vpi_get             (PLI_INT32 property, vpiHandle object)."},
   {"get64",           pyvpi_Get64,            METH_VARARGS,   "PLI_INT64  vpi_get64           (PLI_INT32 property, vpiHandle object)."},
   {"getStr",          pyvpi_GetStr,           METH_VARARGS,   "PLI_BYTE8 *vpi_get_str         (PLI_INT32 property, vpiHandle object)."},
   {"registerCb",      pyvpi_RegisterCb,       METH_VARARGS,   "vpiHandle  vpi_register_cb     (p_cb_data cb_data_p)."},
   {"removeCb",        pyvpi_RemoveCb,         METH_VARARGS,   "PLI_INT32  vpi_remove_cb       (vpiHandle cb_obj)."},
   {"getCbInfo",       pyvpi_GetCbInfo,        METH_VARARGS,   "void       vpi_get_cb_info     (vpiHandle object, <out>p_cb_data cb_data_p)."},
   {"registerSysTf",   pyvpi_RegisterSysTf,    METH_VARARGS,   "vpiHandle  vpi_register_systf  (p_systf_data systf_data_p)."},
   {"getSysTfInfo",    pyvpi_GetSysTfInfo,     METH_VARARGS,   "void       vpi_get_systf_info  (vpiHandle object, <out>p_systf_data systf_data_p)."},
   {"printf",           pyvpi_Print,               METH_VARARGS,   "print function for vpi_printf"},
   {"getTime",         pyvpi_GetTime,          METH_VARARGS,   "void       vpi_get_time      (p_vpi_time time,vpiHandle obj)."},
   {"control",           pyvpi_Control,           METH_VARARGS,   "contorl"},
   {"setDebugLevel",   pyvpi_SetDebugLevel,       METH_VARARGS,   "set pyvpi debug print level."},
   {NULL, NULL, 0, NULL}        /* Sentinel */
};


//Module initial here
PyMODINIT_FUNC initpyvpi(void)
{
    PyObject *m;
    //Check user type is ready..
    if (PyType_Ready(&pyvpi_value_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_value_Type is not Ready.\n")); 
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_value_Type is <0x%lx>.\n",&pyvpi_value_Type));

    if (PyType_Ready(&pyvpi_cbdata_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_cbdata_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_cbdata_Type is <0x%lx>.\n",&pyvpi_cbdata_Type));

    if (PyType_Ready(&pyvpi_time_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_time_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_time_Type is <0x%lx>.\n",&pyvpi_time_Type));

    if (PyType_Ready(&pyvpi_strengthval_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_strengthval_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_strengthval_Type is <0x%lx>.\n",&pyvpi_strengthval_Type));
    
    if (PyType_Ready(&pyvpi_vector_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_vector_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_vector_Type is <0x%lx>.\n",&pyvpi_vector_Type));
    
    if (PyType_Ready(&pyvpi_handle_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_handle_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_handle_Type is <0x%lx>.\n",&pyvpi_handle_Type));

    if (PyType_Ready(&pyvpi_delays_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_delays_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_delays_Type is <0x%lx>.\n",&pyvpi_delays_Type));
    
    if (PyType_Ready(&pyvpi_systfdata_Type) < 0)
    {
        pyvpi_error(sprintf(print_buffer, "pyvpi_systfdata_Type is not Ready.\n"));
        return;
    }
    pyvpi_verbose(sprintf(print_buffer, "pyvpi_systfdata_Type is <0x%lx>.\n",&pyvpi_systfdata_Type));


    //Initial the module.
    m = Py_InitModule("pyvpi", pyvpi_Methods);
    if (m == NULL)
        return;
    
    //Add vpi Error in pyvpi module.
    VpiError = PyErr_NewException("pyvpi.vpiError", NULL, NULL);
    Py_INCREF(VpiError);
    PyModule_AddObject(m, "vpiError", VpiError);
    //return;
    //Add python Error in pyvpi module.
    PyError = PyErr_NewException("pyvpi.PyError", NULL, NULL);
    Py_INCREF(PyError);
    PyModule_AddObject(m, "PyError", PyError);
    
    //Add user type.
    Py_INCREF(&pyvpi_value_Type);
    PyModule_AddObject(m, "Value", (PyObject *)&pyvpi_value_Type);
    Py_INCREF(&pyvpi_cbdata_Type);
    PyModule_AddObject(m, "CbData", (PyObject *)&pyvpi_cbdata_Type);
    Py_INCREF(&pyvpi_time_Type);
    PyModule_AddObject(m, "Time", (PyObject *)&pyvpi_time_Type);
    Py_INCREF(&pyvpi_strengthval_Type);
    PyModule_AddObject(m, "Strength", (PyObject *)&pyvpi_strengthval_Type);
    Py_INCREF(&pyvpi_vector_Type);
    PyModule_AddObject(m, "Vector", (PyObject *)&pyvpi_vector_Type);
    Py_INCREF(&pyvpi_handle_Type);
    PyModule_AddObject(m, "Handle", (PyObject *)&pyvpi_handle_Type);
    Py_INCREF(&pyvpi_delays_Type);
    PyModule_AddObject(m, "Delays", (PyObject *)&pyvpi_delays_Type);    
    Py_INCREF(&pyvpi_systfdata_Type);
    PyModule_AddObject(m, "SysTfData", (PyObject *)&pyvpi_systfdata_Type);
}

//============================================================================
PLI_INT32 pyvpi_StartSim(p_cb_data cb_data_p)
{
    char *pyvpi_start =    "+pyvpi+start=";    //When this sim is start , execute what?
    s_vpi_vlog_info info;
    int i = 0;
    char *p,*q;

    vpi_get_vlog_info(&info);        
    for(i = 0; i<info.argc; i++) {
        q = info.argv[i];
        p = pyvpi_start;
        for(;*p != '\0' && *q != '\0';p++,q++){
            if(*p != *q) break;
        }    
        if(*p == '\0'){
            PyObject* py_fp;
            py_fp = PyFile_FromString(q, "r");
            PyRun_SimpleFile(PyFile_AsFile(py_fp),q);
            break;
        }
    }
    return 0;
}

PLI_INT32 pyvpi_EndSim(p_cb_data cb_data_p)
{
    pyvpi_debug(sprintf(print_buffer,"python begin env finalize.\n"));
    Py_Finalize();
    pyvpi_debug(sprintf(print_buffer,"python end env finalize.\n"));
    return 0;
}
/*****************************************************************************
 * pyvpi_RegisterCallbacks
 * Registers test functions with the simulator.
 *****************************************************************************/
void pyvpi_RegisterCallbacks (void)
{
    static s_cb_data cb_start_sim = {cbStartOfSimulation,pyvpi_StartSim};
    static s_cb_data cb_end_sim   = {cbEndOfSimulation,pyvpi_EndSim};
    vpi_register_cb(&cb_start_sim);
    vpi_register_cb(&cb_end_sim);
}

//============================================================================
PLI_INT32 
pyvpi_main( PLI_BYTE8 *user_data )
{
    vpiHandle self;
    vpiHandle arg_iter;
    vpiHandle arg;
    s_vpi_value val;
    PyObject* py_fp;

    val.format = vpiStringVal;
    self = vpi_handle(vpiSysTfCall,NULL);
    arg_iter = vpi_iterate(vpiArgument,self);
    arg =vpi_scan(arg_iter);
    if(CheckError()) {
        return -1;
    }
    vpi_get_value(arg,&val);
    py_fp = PyFile_FromString(val.value.str, "r");
    PyRun_SimpleFile(PyFile_AsFile(py_fp),val.value.str);
    return 0;
}

PLI_INT32 
pyvpi_main_check( PLI_BYTE8 *user_data )
{
    vpiHandle self;
    vpiHandle arg_iter;
    vpiHandle arg;
    PLI_INT32 index = 0;
    PLI_INT32 re = 0;
    self = vpi_handle(vpiSysTfCall,NULL);
    arg_iter = vpi_iterate(vpiArgument,self);
    if(!(re = CheckError()) && arg_iter){
        while(arg =vpi_scan(arg_iter)){
            if(re = CheckError())
                break;
            switch(index){
            case 0 :
                if(vpi_get(vpiType,arg) == vpiConstant &&
                    vpi_get(vpiConstType,arg) == vpiStringConst){
                }
                else {
                    pyvpi_fatal(sprintf(print_buffer,"The 1st of pyvpi_main must be a "
                        "path string which indicate a py file.\n"));
                }
                break;
            default :
                pyvpi_fatal(sprintf(print_buffer,"In this version, pyvpi only accept one"
                    " string arg.\n"));
                break;
            }
            index++;
            vpi_free_object(arg);
        }
    }
    if(index != 1) {
        pyvpi_fatal(sprintf(print_buffer,"In this version, pyvpi only/must accept one"
                    " string arg.\n"));
    }
    return re;
}

/*****************************************************************************
 * pyvpi_RegisterTfs
 * Registers test functions with the simulator.
 *****************************************************************************/
void pyvpi_RegisterTfs( void )
{
    s_vpi_systf_data    systf_data;
    vpiHandle            systf_handle;
    char *argv[]     =    {"-v"};
    char *pyvpi_load =    "+pyvpi+load=";    //When this lib is load , execute what?

    systf_data.type        = vpiSysTask;
    systf_data.sysfunctype = 0;
    systf_data.tfname      = "$pyvpi_main";
    systf_data.calltf      = pyvpi_main;
    systf_data.compiletf   = pyvpi_main_check;
    systf_data.sizetf      = 0;
    systf_data.user_data   = 0;
    systf_handle = vpi_register_systf( &systf_data );
    vpi_free_object( systf_handle );

    //We must initial Python here so we can use python register 
    //System task and function.
    pyvpi_debug(sprintf(print_buffer,"python begin env initial.\n"));
    Py_Initialize();
    PySys_SetArgv(1,argv);
    pyvpi_debug(sprintf(print_buffer,"python end env initial.\n"));

    {
        s_vpi_vlog_info info;
        int i = 0;
        char *p,*q;

        vpi_get_vlog_info(&info);            
        for(i = 0; i<info.argc; i++) {
            q = info.argv[i];
            p = pyvpi_load;
            for(;*p != '\0' && *q != '\0';p++,q++){
                if(*p != *q) break;
            }
            if(*p == '\0') break;
        }
        if(*p == '\0'){
            //Pass load filename from args
            PyObject* py_fp;
            py_fp = PyFile_FromString(q, "r");
            PyRun_SimpleFile(PyFile_AsFile(py_fp),q);
        }
        else {
            //Default pyvpi load file.
            if(access("pyvpi.load",0) == 0) {
                PyObject* py_fp;
                py_fp = PyFile_FromString("pyvpi.load", "r");
                PyRun_SimpleFile(PyFile_AsFile(py_fp),"pyvpi.load");
            }
        }
    }
}

/*****************************************************************************
 * Required structure for initializing VPI routines.
 *****************************************************************************/

void (*vlog_startup_routines[])() = {
    pyvpi_RegisterTfs,
    pyvpi_RegisterCallbacks,
    0
};

/*****************************************************************************/
