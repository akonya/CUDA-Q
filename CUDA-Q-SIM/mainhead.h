// =============================================
//   Hold all headers to keep things nice    
// =============================================

#ifndef __MAINHEAD_H__
#define __MAINHEAD_H__

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <cuda_texture_types.h>
#include <texture_fetch_functions.h>
#include <texture_types.h>


#include "gpuinfo.h"
#include "errorhandle.h"
#include "datastruct.h"
#include "classstruct.h"
#include "getmesh.h"
#include "getAs.h"
#include "packdata.h"
#include "texdef.h"
#include "rundynamics.h"
#include "datatodevice.h"
#include "parameters.h"
#include "anyerrors.h"
#include "exit_program.h"
#include "printVTKframe.h"

#include "forceKernel.h"
#include "forceKernelIO.h"
#include "forceCalc.h"

#include "updateKernel.h"
#include "updateKernelIO.h"
#include "updateCalc.h"

#include "getEnergy.h"
#include "getQ.h"









#endif //__MAINHEAD_H__
