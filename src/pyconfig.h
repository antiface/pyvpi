#ifndef __PYVPI_CONFIG__
#define __PYVPI_CONFIG__

#define PYVPI_DEBUG

#include "pyvector.h"
#include "pytime.h"
#include "pystrength.h"
#include "pyhandle.h"
#include "pyvalue.h"
#include "pycbdata.h"
#include "pysystfdata.h"

#include "pyvpi.h"

#ifndef SVPI_TYPES
#define SVPI_TYPES
typedef int64_t	 		PLI_INT64;
typedef uint64_t	 	PLI_UINT64;
#endif

extern PyTypeObject pyvpi_value_Type;
extern PyTypeObject pyvpi_cbdata_Type;
extern PyTypeObject pyvpi_time_Type;
extern PyTypeObject pyvpi_strengthval_Type;
extern PyTypeObject pyvpi_vector_Type;
extern PyTypeObject pyvpi_handle_Type;
extern PyTypeObject pyvpi_delays_Type;
extern PyTypeObject pyvpi_systfdata_Type;
#endif
