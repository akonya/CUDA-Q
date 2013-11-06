#ifndef __FORCECALC_H__
#define __FORCECALC_H__

#include "mainhead.h"
#include "parameters.h"


//=============================================================
//calculate forces on all 4 nodes in tetrahedra
//=============================================================
__device__ void force_calc(float Ainv[16] 
                          ,float Ploc[4*degreeP]
                          ,float (&fPloc)[4*degreeP] 
                          ,float myVol){
  //dummy force for now
  for (int i=0;i<4*degreeP;i++){
    fPloc[i] = 0.0000001;
  }//i
}//force_calc
#endif//__FORCECALC_H__
