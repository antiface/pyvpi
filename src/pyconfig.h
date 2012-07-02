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
#ifndef FADDR_MARCO
#define FADDR_MARCO "<0x%llx>"
#endif
#else
#define PYVPI_ALIGN 4
#ifndef FADDR_MARCO
#define FADDR_MARCO "<0x%x>"
#endif
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

//Utils functions
PLI_INT32 pyvpi_verbose(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_debug(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_trace(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_note(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_warning(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_error(PLI_BYTE8 * format, ...);
PLI_INT32 pyvpi_fatal(PLI_BYTE8 * format, ...);
#endif
