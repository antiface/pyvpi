#include "pyvpi.h"

/*****************************************************************************
 * This is all code for python.
/*****************************************************************************/
//We Define two errors, if vpi call function is error, VpiError will be assert,
//else if python error, PyError will be set.
static PyObject *VpiError;
static PyObject *PyError;
/*****************************************************************************
 * pyvpi_CheckError()
 * Checks if an error was reported by the last vpi function called
 * and, if so, set VpiError and return error code.
 *****************************************************************************/
int pyvpi_CheckError( void )
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
 static PyObject* pyvpi_HandleByName(PyObject *self, PyObject *args)
 {
     PLI_BYTE8 *name;
     p_pyvpi_handle scope,oans;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "sO", &name,&scope))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (str,pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_handle_by_name(name,scope->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
     oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
     return (PyObject *)oans;
 }
/* 
 * XXTERN vpiHandle  vpi_handle_by_index PROTO_PARAMS((vpiHandle object,
 *                                                     PLI_INT32 indx));
 */
 static PyObject* pyvpi_HandleByIndex(PyObject *self, PyObject *args)
 {
     p_pyvpi_handle object,oans;
     PLI_INT32 indx;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "kO", &object,&indx))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (long,pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_handle_by_index(object->_vpi_handle,indx);
     if(pyvpi_CheckError())
        return NULL;
     oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
     return (PyObject *)oans;  
 }

/* for traversing relationships */
/*
    XXTERN vpiHandle  vpi_handle          PROTO_PARAMS((PLI_INT32 type,
                                                        vpiHandle refHandle));
*/
 static PyObject* pyvpi_Handle(PyObject *self, PyObject *args)
 {
     p_pyvpi_handle refHandle,oans;
     PLI_INT32 type;
     vpiHandle ans;   
     if (!PyArg_ParseTuple(args, "iO", &type,&refHandle)) 
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_handle(type,refHandle->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
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
 static PyObject* pyvpi_Iterate(PyObject *self, PyObject *args)
 {
     PLI_INT32 type;
     p_pyvpi_handle refHandle,oans;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "iO", &type,&refHandle))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_iterate(type,refHandle->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
     oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
     return (PyObject *)oans;   
 }
/* 
    XXTERN vpiHandle  vpi_scan            PROTO_PARAMS((vpiHandle iterator));
*/
 static PyObject* pyvpi_Scan(PyObject *self, PyObject *args)
 {
     p_pyvpi_handle iterator,oans;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "O", &iterator))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_scan(iterator->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
     if(ans != NULL) {
        oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
     }
     else {
        Py_INCREF(Py_None);
        oans = (p_pyvpi_handle) Py_None;
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
 static PyObject* pyvpi_Get(PyObject *self, PyObject *args)
 {
     PLI_INT32 property;
     p_pyvpi_handle object;
     PLI_INT32 ans;
     if (!PyArg_ParseTuple(args, "iO", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,pyvpi._vpi_Handle).");
         return NULL;
     }
     ans = vpi_get(property,object->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("I", ans);
 }

 static PyObject* pyvpi_Get64(PyObject *self, PyObject *args)
 {
     PLI_INT32 property;
     p_pyvpi_handle object;
     PLI_INT64 ans;
     if (!PyArg_ParseTuple(args, "iO", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_get(property,object->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;        
     return Py_BuildValue("I", ans);
 }

 static PyObject* pyvpi_GetStr(PyObject *self, PyObject *args)
 {
     PLI_INT32 property;
     p_pyvpi_handle object;
     char  *ans;
     if (!PyArg_ParseTuple(args, "iO", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,pyvpi._vpiHandle).");
         return NULL;
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
  static PyObject* pyvpi_RegisterCb(PyObject *self, PyObject *args) //TBD cbData will store cb_h,maybe need update 
 {                                                                  //the args of vpi_remove_cb and vpi_get_cb_info.
     s_pyvpi_cbdata*  cbdata;
     vpiHandle  ans;
     p_pyvpi_handle oans; 
     if (!PyArg_ParseTuple(args, "O", &cbdata))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi.CbData).");
         return NULL;
     }
     ans = vpi_register_cb(&cbdata->_vpi_cbdata);
     cbdata->cb_h = ans;     
     if(pyvpi_CheckError())
        return NULL;
     oans = (p_pyvpi_handle) _pyvpi_handle_New(ans);
     return (PyObject *)oans;   
 }
 
  static PyObject* pyvpi_RemoveCb(PyObject *self, PyObject *args)
 {
     p_pyvpi_handle  cb_obj;
     PLI_INT32  ans;
     if (!PyArg_ParseTuple(args, "O", &cb_obj))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi._vpiHandle).");
         return NULL;
     }
     ans = vpi_remove_cb(cb_obj->_vpi_handle);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("i", ans);
 }
 
  static PyObject* pyvpi_GetCbInfo(PyObject *self, PyObject *args)
 {
     p_pyvpi_handle  object,trgobj;
     p_pyvpi_cbdata  cbdata;
     PyObject*       pdict = PyDict_New();
     PyObject*       ptpl = PyTuple_New(0);
     if (!PyArg_ParseTuple(args, "O", &object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi._vpiHandle).");
         return NULL;
     }
     //Initial cbdata;
    cbdata = (p_pyvpi_cbdata) pyvpi_cbdata_New(&pyvpi_cbdata_Type,ptpl,pdict);
    cbdata->cb_h = object->_vpi_handle;
    vpi_get_cb_info(object->_vpi_handle,&cbdata->_vpi_cbdata);
    // Add trgobj info.    
    trgobj = (p_pyvpi_handle) _pyvpi_handle_New(cbdata->_vpi_cbdata.obj);
    //Initial cbData...
    PyDict_SetItemString(pdict,"trgobj",(PyObject*) trgobj);
    Py_DECREF(trgobj);
    pyvpi_cbdata_Init(cbdata,ptpl,pdict);    
    Py_DECREF(ptpl);
    Py_DECREF(pdict);
    if(pyvpi_CheckError())
       return NULL;
    return (PyObject*) cbdata;
 }
 
 static PyMethodDef pyvpi_Methods[] = {
    /* for obtaining handles */
    {"HandleByName",    pyvpi_HandleByName,     METH_VARARGS,   "vpiHandle  vpi_handle_by_name (PLI_BYTE8 *name, vpiHandle scope)."},
    {"HandleByIndex",   pyvpi_HandleByIndex,    METH_VARARGS,   "vpiHandle  pyvpi_HandleByIndex (vpiHandle object, PLI_INT32 indx)."},
    /* for traversing relationships */
    {"Handle",          pyvpi_Handle,           METH_VARARGS,   "vpiHandle  vpi_handle   (PLI_INT32 type, vpiHandle refHandle)"},
    //{"HandleMulti",     pyvpi_HandleMulti,      METH_VARARGS,   "vpiHandle  vpi_handle_multi    (PLI_INT32 type, vpiHandle refHandle1, vpiHandle refHandle2, ... )"},
    {"Iterate",         pyvpi_Iterate,          METH_VARARGS,   "vpiHandle  vpi_iterate (PLI_INT32 type, vpiHandle refHandle)"},
    {"Scan",            pyvpi_Scan,             METH_VARARGS,   "vpiHandle  vpi_scan    (vpiHandle iterator)"},
    /* for processing properties */
    {"Get",             pyvpi_Get,              METH_VARARGS,   "PLI_INT32  vpi_get             (PLI_INT32 property, vpiHandle object)."},
    {"Get64",           pyvpi_Get64,            METH_VARARGS,   "PLI_INT64  vpi_get64           (PLI_INT32 property, vpiHandle object)."},
    {"GetStr",          pyvpi_GetStr,           METH_VARARGS,   "PLI_BYTE8 *vpi_get_str         (PLI_INT32 property, vpiHandle object)."},
    {"RegisterCb",      pyvpi_RegisterCb,       METH_VARARGS,   "vpiHandle  vpi_register_cb     (p_cb_data cb_data_p)."},
    {"RemoveCb",        pyvpi_RemoveCb,         METH_VARARGS,   "PLI_INT32  vpi_remove_cb       (vpiHandle cb_obj)."},
    {"GetCbInfo",       pyvpi_GetCbInfo,        METH_VARARGS,   "void       vpi_get_cb_info     (vpiHandle object, <out>p_cb_data cb_data_p)."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


//Module initial here
PyMODINIT_FUNC initpyvpi(void)
{
    PyObject *m;
    //Check user type is ready..
    if (PyType_Ready(&pyvpi_value_Type) < 0)
    {
        vpi_printf("Error : pyvpi_value_Type is not Ready.\n");        
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_value_Type is <0x%lx>.\n",&pyvpi_value_Type);
#endif

    if (PyType_Ready(&pyvpi_cbdata_Type) < 0)
    {
        vpi_printf("Error : pyvpi_cbdata_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_cbdata_Type is <0x%lx>.\n",&pyvpi_cbdata_Type);
#endif

    if (PyType_Ready(&pyvpi_time_Type) < 0)
    {
        vpi_printf("Error : pyvpi_time_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_time_Type is <0x%lx>.\n",&pyvpi_time_Type);
#endif

    if (PyType_Ready(&pyvpi_strengthval_Type) < 0)
    {
        vpi_printf("Error : pyvpi_strengthval_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_strengthval_Type is <0x%lx>.\n",&pyvpi_strengthval_Type);
#endif
    
    if (PyType_Ready(&pyvpi_vector_Type) < 0)
    {
        vpi_printf("Error : pyvpi_vector_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_vector_Type is <0x%lx>.\n",&pyvpi_vector_Type);
#endif
    
    if (PyType_Ready(&pyvpi_handle_Type) < 0)
    {
        vpi_printf("Error : pyvpi_handle_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_handle_Type is <0x%lx>.\n",&pyvpi_handle_Type);
#endif

    if (PyType_Ready(&pyvpi_delays_Type) < 0)
    {
        vpi_printf("Error : pyvpi_delays_Type is not Ready.\n");
        return;
    }
#ifdef PYVPI_DEBUG    
    vpi_printf("[PYVPI_DEBUG] pyvpi_delays_Type is <0x%lx>.\n",&pyvpi_delays_Type);
#endif

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
    PyModule_AddObject(m, "vpiHandle", (PyObject *)&pyvpi_handle_Type);
    Py_INCREF(&pyvpi_delays_Type);
    PyModule_AddObject(m, "Delays", (PyObject *)&pyvpi_delays_Type);    
}

//============================================================================
PLI_INT32 pyvpi_StartSim(p_cb_data cb_data_p)
{
    vpi_printf("pyvpi_StartSim\n");
    Py_Initialize();
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
