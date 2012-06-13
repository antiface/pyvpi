//
#ifndef __PYVPI_H__
#define __PYVPI_H__

#include "Python.h"
#include "vpi_user.h"
#include "sv_vpi_user.h"

#include "pyconfig.h"

static PyObject *VpiError;
static PyObject *PyError;

static PyObject *SysTfDict;         //This is a dict used to store all system task and function in register.
static PyObject *CallbackDict;      //This is a dict used to store all register callback function.
/* ------------------------------------------------------------------------- */
extern int pyvpi_CheckError( void );
/* ------------------------------------------------------------------------- */

#define PRINT_VERBOSE   10
#define PRINT_DEBUG     20
#define PRINT_TRACE     30
#define PRINT_NOTE      40
#define PRINT_WARNING   50
#define PRINT_ERROR     60
#define PRINT_FATAL     70

static int  print_level     = PRINT_VERBOSE;
static char print_buffer[2048];

#define pyvpi_verbose(str)  \
    if(print_level <= PRINT_VERBOSE) { \
    str;\
    vpi_printf("VERBOSE : %s",print_buffer); \
    }

#define pyvpi_debug(str)  \
    if(print_level <= PRINT_DEBUG) { \
    str;\
    vpi_printf("DEBUG : %s",print_buffer); \
    }

#define pyvpi_trace(str)  \
    if(print_level <= PRINT_TRACE) { \
    str;\
    vpi_printf("TRACE : %s",print_buffer); \
    }

#define pyvpi_note(str)  \
    if(print_level <= PRINT_NOTE) { \
    str;\
    vpi_printf("NOTE : %s",print_buffer); \
    }

#define pyvpi_warning(str)  \
    if(print_level <= PRINT_WARNING) { \
    str;\
    vpi_printf("WARNING : %s",print_buffer); \
    }

#define pyvpi_error(str)  \
    if(print_level <= PRINT_ERROR) { \
    str;\
    vpi_printf("ERROR : %s",print_buffer); \
    }

#define pyvpi_fatal(str)  \
    if(print_level <= PRINT_FATAL) { \
    str;\
    vpi_printf("FATAL : %s",print_buffer); \
    vpi_control(vpiFinish); \
    }

#endif

