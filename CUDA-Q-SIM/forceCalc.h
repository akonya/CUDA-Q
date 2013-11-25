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
    //common constants
    float c1 = 0.4082482904638631;   // 1/sqrt(6)
    float c2 = 0.7071067811865475;

    //constructing tensors to be used
    //T^i_jk = T_ijk dimensions T_533  indexed by T[9*i+3*j+k]
    float T[45]={-c1,0.,0.,0.,c1,0.,0.,0.,2.0*c1 \
                 ,c2,0.,0.,0.,-c2,0.,0.,0.,0. \
                 ,0.,c2,0.,c2,0.,0.,0.,0.,0., \
                 ,0.,0.,c2,0.,0.,0.,c2,0.,0. \
                 ,0.,0.,0.,0.,0.,c2,0.,c2,0.};
   // b_ij dimensinos b_34  indexed by b[i*4+j]
   float b[12] = {0.,1.,0.,0. \
                 ,0.,0.,1.,0. \
                 ,0.,0.,0.,1.}; 


   

  //dummy force for now
  for (int i=0;i<4*degreeP;i++){
    fPloc[i] = 0.0000001;
  }//i
}//force_calc
#endif//__FORCECALC_H__
