#ifndef __PYVPI_CONFIG__
#define __PYVPI_CONFIG__

#define PYVPI_DEBUG

#include "pyvector.h"
#include "pytime.h"
#include "pystrength.h"
#include "pyhandle.h"
#include "pyvalue.h"
#include "pycbdata.h"

#include "pyvpi.h"

extern PyTypeObject pyvpi_value_Type;
extern PyTypeObject pyvpi_cbdata_Type;
extern PyTypeObject pyvpi_time_Type;
extern PyTypeObject pyvpi_strengthval_Type;
extern PyTypeObject pyvpi_vector_Type;
extern PyTypeObject pyvpi_handle_Type;
extern PyTypeObject pyvpi_delays_Type;
#endif
