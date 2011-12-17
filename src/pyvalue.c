//The 
#include "pyvalue.h"

//Type define here
PyTypeObject pyvpi_value_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._Value",             /*tp_name*/
    sizeof(s_pyvpi_value),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_value_Dealloc, /*tp_dealloc*/    
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
    "pyvpi value objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_value_methods,       /* tp_methods */
    pyvpi_value_members,       /* tp_members */
    pyvpi_value_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_value_Init, /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_value_New,           /* tp_new */
};

void pyvpi_value_Dealloc(p_pyvpi_value self)
{
    //Free self.
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is release,ptr is 0x%x.\n",self);
#endif
    if(self->cache_ptr != NULL) free(self->cache_ptr);
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds)
{    
    static char *kwlist[] = {"format", NULL};
    
    self->_vpi_value.format = vpiHexStrVal; //Default value.
    self->_vpi_value.value.str = self->cache_ptr;
    self->_vpi_value.value.str[0] = 0;
    self->vec_size = 0;    
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,                                      
                                      &self->_vpi_value.format))
        return -1;
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is Initial,format is 0x%x.\n",self->_vpi_value.format);
#endif
    return 0;
}

PyObject * pyvpi_value_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    p_pyvpi_value   self;
    int i = 0;
    self = (p_pyvpi_value)type->tp_alloc(type, 0);
    if(self == NULL) 
        return NULL;
    self->cache_size = 128;     //Default cache value is 128 bytes.
    self->cache_ptr  = (void *) malloc(self->cache_size);   
    if(self->cache_ptr == NULL) {
        PyErr_SetString(PyExc_MemoryError,
                        "There is no enouth memory for value assign.");    
        Py_DECREF(self);
        return NULL;
    }   
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is allocate,ptr is <0x%x>, type ptr is <0x%x>.\n",self,type);
#endif 
    return (PyObject *) self;
}

//Get/Set
PyObject * s_pyvpi_value_getvalue(s_pyvpi_value *self, void *closure)
{
    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:
            //Need malloc new space or not??
            return Py_BuildValue("s",self->_vpi_value.value.str);
        case vpiScalarVal:
            return Py_BuildValue("i",self->_vpi_value.value.scalar);
        case vpiIntVal:
            return Py_BuildValue("i",self->_vpi_value.value.integer);
        case vpiRealVal:
            return Py_BuildValue("d",self->_vpi_value.value.real);
        case vpiVectorVal:  //TBD
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            Py_INCREF(Py_None);
            return Py_None;
    }
}
int        s_pyvpi_value_setvalue(s_pyvpi_value *self, PyObject *value, void *closure)
{
     char * str;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set index to NULL.");
        return -1;
    }

    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:           
            if (! PyString_Check(value)) {
                PyErr_SetString(PyExc_TypeError,
                                "The value must be a string<Current format is string>.");
                return -1;
            }
            str = PyString_AS_STRING(value);
            if(strlen(str) > (self->cache_size - 1))
            {
                //new space will be allocate.
                char* nstr = (char *) malloc(self->cache_size * 2);
                if(nstr != NULL) {
                    self->cache_size = self->cache_size *2;
                    free(self->cache_ptr);
                    self->cache_ptr = nstr;                    
                }
                else {
                    PyErr_SetString(PyExc_MemoryError,
                                    "There is no enouth memory for value assign.");
                    return -1;
                }
            }            
            strcpy(self->cache_ptr,str);
            self->_vpi_value.value.str = self->cache_ptr;
        case vpiScalarVal:
            if (! PyInt_Check(value) || PyInt_AS_LONG(value) < 0 || PyInt_AS_LONG(value) > 3) {
                PyErr_SetString(PyExc_TypeError,
                                "The value must be vpi[0,1,X,Z]<Current format is vpiScalarVal>.");
                return -1;
            }
            self->_vpi_value.value.scalar = PyInt_AS_LONG(value);
        case vpiIntVal:
            if (! PyInt_Check(value)) {
                PyErr_SetString(PyExc_TypeError,
                                "The value must be an int<Current format is vpiIntVal>.");
                return -1;
            }
            self->_vpi_value.value.integer = PyInt_AS_LONG(value);            
        case vpiRealVal:
            if (! PyFloat_Check(value)) {
                PyErr_SetString(PyExc_TypeError,
                                "The value must be an float<Current format is vpiRealVal>.");
                return -1;
            }
            self->_vpi_value.value.real = PyFloat_AsDouble(value);              
        case vpiVectorVal:  //TBD How to deal with Vector? So confused.
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            return -1;
    }
    return 0;
}

/*
 * Copy s_vpi_value structure - must first allocate pointed to fields.
 * nvalp must be previously allocated.
 * Need to first determine size for vector value.
 */
void copy_vpi_value(s_vpi_value *nvalp, s_vpi_value *ovalp, PLI_INT32 blen, PLI_INT32 nd_alloc)
{
    //Need Check allocate failed.. TBD
    int i;
    PLI_INT32 numvals;
    nvalp->format = ovalp->format;
    switch (nvalp->format) {
    /* all string values */
    case vpiBinStrVal:
    case vpiOctStrVal:
    case vpiDecStrVal:
    case vpiHexStrVal:
    case vpiStringVal:
        if (nd_alloc) {
            if(nvalp->value.str != NULL) free(nvalp->value.str);
            nvalp->value.str = malloc(nd_alloc);
        }
        else {
            strcpy(nvalp->value.str, ovalp->value.str);
        }
        break;
    case vpiScalarVal:
        nvalp->value.scalar = ovalp->value.scalar;
        break;
    case vpiIntVal:
        nvalp->value.integer = ovalp->value.integer;
        break;
    case vpiRealVal:
        nvalp->value.real = ovalp->value.real;
        break;
    case vpiVectorVal:
        numvals = (blen + 31) >> 5;
        if (nd_alloc)
        {
            if(nvalp->value.vector != NULL) free(nvalp->value.vector);
            nvalp->value.vector = (p_vpi_vecval) malloc(nd_alloc);
        }
        /* t_vpi_vecval is really array of the 2 integer a/b sections */
        /* memcpy or bcopy better here */
        for (i = 0; i <numvals; i++)
        nvalp->value.vector[i] = ovalp->value.vector[i];
        break;
    case vpiStrengthVal:
        if (nd_alloc)
        {
            if(nvalp->value.strength != NULL) free(nvalp->value.strength);
            nvalp->value.strength = (p_vpi_strengthval) malloc(nd_alloc);
        }
        /* assumes C compiler supports struct assign */
        *(nvalp->value.strength) = *(ovalp->value.strength);
        break;
    case vpiTimeVal:
        nvalp->value.time = (p_vpi_time) malloc(sizeof(s_vpi_time));
        /* assumes C compiler supports struct assign */
        *(nvalp->value.time) = *(ovalp->value.time);
        break;
        /* not sure what to do here? */
    case vpiObjTypeVal: case vpiSuppressVal:
    vpi_printf(
        "**ERR: cannot copy vpiObjTypeVal or vpiSuppressVal formats",
        " - not for filled records.\n");
        break;
    }
}

