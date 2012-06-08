#include "pyvpi.h"

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
        PyErr_SetString(PyExc_TypeError,  error_info.message);
    }
    return error_code;
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
    p_pyvpi_handle scope,oans;
    vpiHandle ans;
    if (!PyArg_ParseTuple(args, "sO", &name,&scope))
    {
        PyErr_SetString(VpiError,  "Error args, must be (str,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(scope,&pyvpi_handle_Type)) {
        pyvpi_trace(sprintf(print_buffer, "handleByName 's 2nd arg is "
                    "not pyvpi.Handle type, trade scope as NULL.\n"));
        ans = vpi_handle_by_name(name, NULL);
    }
    else {
        ans = vpi_handle_by_name(name,scope->_vpi_handle);
    }
    if(pyvpi_CheckError())
       return NULL;

    if(ans == NULL) {
        return Py_None;
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
        PyErr_SetString(VpiError,  "Error args, must be (long,pyvpi.Handle).");
        return NULL;
    }
    if (!PyObject_TypeCheck(object,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (long,pyvpi.Handle).");
        return NULL; //TBD
    }
    else {
        ans = vpi_handle_by_index(object->_vpi_handle,indx);
    }
    if(pyvpi_CheckError())
       return NULL;
    if(ans == NULL) {
        return Py_None;
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
        return Py_None;
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
        return Py_None;
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
    p_pyvpi_handle  cb_obj;
    p_pyvpi_cbdata  cbdata;
    PLI_INT32  ans;
    if (!PyArg_ParseTuple(args, "O", &cb_obj))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle|pyvpi.CbData).");
        return NULL;
    }

    if (PyObject_TypeCheck(cb_obj,&pyvpi_cbdata_Type)) {
        cbdata = (p_pyvpi_cbdata) cb_obj;
        cb_obj = (p_pyvpi_handle) cbdata;
    }
    else if (!PyObject_TypeCheck(cb_obj,&pyvpi_handle_Type)) {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.Handle|pyvpi.CbData).");
        return NULL;
    }
    ans = vpi_remove_cb(cb_obj->_vpi_handle);
    cb_obj->is_free = 1;
    pyvpi_verbose(sprintf(print_buffer, "pyvpi.Handle->Handle is "
                    "release,ptr is <0x%lx>.\n", cb_obj->_vpi_handle));
    if(pyvpi_CheckError())
        return NULL;    
    return Py_BuildValue("i", ans);
}

static PyObject* 
pyvpi_GetCbInfo(PyObject *self, PyObject *args)
{
     //There is no use to port this function;
     //TBD
    pyvpi_warning(sprintf(print_buffer,"pyvpi.getCbInfo is not allowed "
                "used in this version!\n"));
    return Py_None;
//# p_pyvpi_handle  object,trgobj;
//# p_pyvpi_cbdata  cbdata;
//# PyObject*       pdict = PyDict_New();
//# PyObject*       ptpl = PyTuple_New(0);
//# if (!PyArg_ParseTuple(args, "O", &object))
//# {
//#     PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi._vpiHandle).");
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
    p_pyvpi_handle oans; 
    if (!PyArg_ParseTuple(args, "O", &systfdata))
    {
        PyErr_SetString(VpiError,  "Error args, must be (pyvpi.SysTfData).");
        return NULL;
    }
    ans = vpi_register_cb(&systfdata->_vpi_systfdata);
    if(pyvpi_CheckError())
       return NULL;
    oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
    return (PyObject *)oans;   
}

static PyObject* 
pyvpi_GetSysTfInfo(PyObject *self, PyObject *args)
{
    //There is no use to port this function;
    pyvpi_warning(sprintf(print_buffer,"pyvpi.getSysTfInfo is not allowed "
                 "used in this version!\n"));
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
    p_pyvpi_time    time;
    PLI_INT32       flags;
    vpiHandle       ans;
    if (!PyArg_ParseTuple(args, "OOOi", &handle, &value, &time, flags))
    {
        PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi.Handle,pyvpi.Value).");
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
    if(Py_TYPE(time) != &pyvpi_time_Type) {    
        //PyErr_SetString(VpiError,  "Error args, 3nd arg must be pyvpi.Time.");
        //return NULL;
        pyvpi_debug(sprintf(print_buffer, "3nd arg of putValue is not pyvpi.Time, "
                    "trade it as NULL"));
        time = NULL;
    }
    ans = vpi_put_value(handle->_vpi_handle,&value->_vpi_value,&time->_vpi_time,flags);
    if(pyvpi_CheckError())
        return NULL;
    if(ans == NULL) {
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
    vpi_get_value(handle->_vpi_handle,&value->_vpi_value);
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
   {"getCbInfo",       pyvpi_GetSysTfInfo,     METH_VARARGS,   "void       vpi_get_systf_info  (vpiHandle object, <out>p_systf_data systf_data_p)."},
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
    char *argv[]   =   {"-v"};
    vpi_printf("pyvpi_StartSim\n");
    Py_Initialize();
    PySys_SetArgv(1,argv);
    return 0;
}

PLI_INT32 pyvpi_EndSim(p_cb_data cb_data_p)
{
    vpi_printf("pyvpi_EndSim\n");
    Py_Finalize();
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
PLI_INT32 pyvpi_printf()
{
    vpi_printf("...123...\n");
    return 1;
}
PLI_INT32 pyvpi_test( PLI_BYTE8 *user_data )
{
    FILE * fp = fopen("./test.py","r");
    PyRun_SimpleFile(fp,"test.py");
    //PyRun_SimpleString("print 'Hello python.'");
    vpi_printf("vpi info from inner.\n");
    fclose(fp);
    return 0;
}

/*****************************************************************************
 * pyvpi_RegisterTfs
 * Registers test functions with the simulator.
 *****************************************************************************/
void pyvpi_RegisterTfs( void )
{
    s_vpi_systf_data systf_data;
    vpiHandle        systf_handle;

    systf_data.type        = vpiSysTask;
    systf_data.sysfunctype = 0;
    systf_data.tfname      = "$test";
    systf_data.calltf      = pyvpi_test;
    systf_data.compiletf   = 0;
    systf_data.sizetf      = 0;
    systf_data.user_data   = 0;
    systf_handle = vpi_register_systf( &systf_data );
    vpi_free_object( systf_handle );
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
