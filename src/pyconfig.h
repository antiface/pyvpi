#ifndef __PYVPI_CONFIG__
#define __PYVPI_CONFIG__

#define PYVPI_DEBUG

#include "pyvector.h"
#include "pytime.h"
#include "pystrength.h"
#include "pycbdata.h"
#include "pyvalue.h"

#include "pyvpi.h"

extern PyTypeObject pyvpi_value_Type;
extern PyTypeObject pyvpi_cbdata_Type;
extern PyTypeObject pyvpi_time_Type;
extern PyTypeObject pyvpi_strengthval_Type;
#endif
