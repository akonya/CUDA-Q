#ifndef __UPDATECALC_H__
#define __UPDATECALC_H__

#include "mainhead.h"
#include "parameters.h"


//=============================================================
// calculate new P's from old P's and fP's
//=============================================================
__device__ void calcP(float (&ploc)[degreeP]
						         ,float (&fPloc)[degreeP]){

  for (int degP=0;degP<degreeP;degP++){
    ploc[degP]+=fPloc[degP]*dt;
  }//degP

}//calcP

#endif//__UPDATECALC_H__
