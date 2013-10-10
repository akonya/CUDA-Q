#ifndef __FORCECALC_H__
#define __FORCECALC_H__

#include "mainhead.h"
#include "parameters.h"


//=============================================================
//calculate forces on all 4 nodes in tetrahedra
//=============================================================
__device__ void force_calc(float *Ainv,float *r0,float *r,float *Q,float (&F)[12],int *TetNodeRank,float *pe,int mytet,float myVol){

}//force_calc
#endif//__FORCECALC_H__
