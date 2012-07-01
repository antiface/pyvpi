#ifndef __PYVPI_CONFIG__
#define __PYVPI_CONFIG__
/*
    Type           ILP64   LP64   LLP64<32BIT>
    char              8      8       8
    short            16     16      16
    int              64     32      32
    long             64     64      32
    long long        64     64      64
    pointer          64     64      64
*/
#ifndef SVPI_TYPES
#define SVPI_TYPES
typedef int64_t          PLI_INT64;
typedef uint64_t         PLI_UINT64;
#endif

#ifdef __LP64__
#define PYVPI_ALIGN 8
#else
#define PYVPI_ALIGN 4
#endif

extern PyTypeObject pyvpi_value_Type;
extern PyTypeObject pyvpi_cbdata_Type;
extern PyTypeObject pyvpi_time_Type;
extern PyTypeObject pyvpi_strengthval_Type;
extern PyTypeObject pyvpi_vector_Type;
extern PyTypeObject pyvpi_handle_Type;
extern PyTypeObject pyvpi_delays_Type;
extern PyTypeObject pyvpi_systfdata_Type;

/*
    Python other modules type;
 */

//Extern pyobject.
PyObject *VpiError;
PyObject *PyError;
PyObject *DumbTuple;
PyObject *DumbDict;


//Common use print macro.
#define PRINT_VERBOSE   10
#define PRINT_DEBUG     20
#define PRINT_TRACE     30
#define PRINT_NOTE      40
#define PRINT_WARNING   50
#define PRINT_ERROR     60
#define PRINT_FATAL     70

static int  print_level     = PRINT_TRACE;
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
