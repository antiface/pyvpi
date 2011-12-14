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
static int pyvpi_CheckError( void )
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
     vpiHandle scope;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "sl", &name,&scope))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (str,int).");
         return NULL;
     }
     ans = vpi_handle_by_name(name,scope);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("l", ans);
 }
/* 
 * XXTERN vpiHandle  vpi_handle_by_index PROTO_PARAMS((vpiHandle object,
 *                                                     PLI_INT32 indx));
 */
 static PyObject* pyvpi_HandleByIndex(PyObject *self, PyObject *args)
 {
     vpiHandle object;
     PLI_INT32 indx;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "li", &object,&indx))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_handle_by_index(object,indx);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("l", ans);
 }

/* for traversing relationships */
/*
    XXTERN vpiHandle  vpi_handle          PROTO_PARAMS((PLI_INT32 type,
                                                        vpiHandle refHandle));
*/
 static PyObject* pyvpi_Handle(PyObject *self, PyObject *args)
 {
     vpiHandle type;
     PLI_INT32 refHandle;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "il", &type,&refHandle))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_handle_by_index(type,refHandle);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("l", ans);
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
     vpiHandle refHandle;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "il", &type,&refHandle))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_iterate(type,refHandle);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("l", ans);
 }
/* 
    XXTERN vpiHandle  vpi_scan            PROTO_PARAMS((vpiHandle iterator));
*/
 static PyObject* pyvpi_Scan(PyObject *self, PyObject *args)
 {
     vpiHandle iterator;
     vpiHandle ans;
     if (!PyArg_ParseTuple(args, "l", &iterator))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int).");
         return NULL;
     }
     ans = vpi_scan(iterator);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("l", ans);
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
     vpiHandle object;
     PLI_INT32 ans;
     if (!PyArg_ParseTuple(args, "il", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_get(property,object);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("i", ans);
 }

 static PyObject* pyvpi_Get64(PyObject *self, PyObject *args)
 {
     PLI_INT32 property;
     vpiHandle object;
     PLI_INT64 ans;
     if (!PyArg_ParseTuple(args, "il", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_get(property,object);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("i", ans);
 }

 static PyObject* pyvpi_GetStr(PyObject *self, PyObject *args)
 {
     PLI_INT32 property;
     vpiHandle object;
     char  *ans;
     if (!PyArg_ParseTuple(args, "il", &property,&object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int,int).");
         return NULL;
     }
     ans = vpi_get_str(property,object);
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
  static PyObject* pyvpi_RegisterCb(PyObject *self, PyObject *args)
 {
     s_pyvpi_cbdata*  cbdata;
     vpiHandle  ans;     
     if (!PyArg_ParseTuple(args, "O", &cbdata))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (pyvpi.CbData).");
         return NULL;
     }
     vpi_printf("pyvpi_RegisterCb is running0...%d,%x\n",cbdata->_vpi_cbdata.reason,cbdata->_vpi_cbdata.cb_rtn);
     ans = vpi_register_cb(&cbdata->_vpi_cbdata); 
     vpi_printf("pyvpi_RegisterCb is running1...\n");
     cbdata->cb_h = ans;     
     if(pyvpi_CheckError())
        return NULL;
     vpi_printf("pyvpi_RegisterCb is running2...\n");
     return Py_BuildValue("l", ans);
 }
 
  static PyObject* pyvpi_RemoveCb(PyObject *self, PyObject *args)
 {
     vpiHandle  cb_obj;
     PLI_INT32  ans;
     if (!PyArg_ParseTuple(args, "l", &cb_obj))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int).");
         return NULL;
     }
     ans = vpi_remove_cb(cb_obj);
     if(pyvpi_CheckError())
        return NULL;
     return Py_BuildValue("i", ans);
 }
 
  static PyObject* pyvpi_GetCbInfo(PyObject *self, PyObject *args)
 {
     vpiHandle  object;
     p_pyvpi_cbdata cbdata;
     if (!PyArg_ParseTuple(args, "l", &object))
     {
         PyErr_SetString(PyExc_TypeError,  "Error args, must be (int).");
         return NULL;
     }
     //Initial cbdata;
     cbdata = (p_pyvpi_cbdata) pyvpi_cbdata_Type.tp_alloc(&pyvpi_cbdata_Type, 0);
     Py_INCREF(cbdata);
     vpi_get_cb_info(object,&cbdata->_vpi_cbdata);
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
        return;
    if (PyType_Ready(&pyvpi_cbdata_Type) < 0)
        return;
        
    //
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
    vpi_printf("vpi info from inner.");
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
