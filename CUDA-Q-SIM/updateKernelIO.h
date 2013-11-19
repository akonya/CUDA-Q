#ifndef __SUMFORCE_H__
#define __SUMFORCE_H__

#include "mainhead.h"
#include "parameters.h"

//===========================================
// read in a sum all forces present on node 
// being executed on this thread
//===========================================
__device__ void getDataUK( int myNode
						, int myNodeRank
						, float (&fPloc)[degreeP]
						, float *fP
						, int fPshift
            , float *P
            , int Pshift
            , float (&ploc)[degreeP]){


	for( int pDeg=0;pDeg<degreeP;pDeg++ ){
    ploc[pDeg] = P[Pshift*pDeg+myNode]; 
		//sum effect forces from each tet this node belongs to 
		for(int nodeRank=0;nodeRank<myNodeRank;nodeRank++){
      fPloc[pDeg]+=fP[fPshift*(degreeP*nodeRank+pDeg)+myNode];
    }//r
	}//ip
	
}//getDataUK

//==========================================
// send updated P's
//==========================================
__device__ void sendDataUK(float (&ploc)[degreeP]
                          ,float *P
                          ,int Pshift
                          ,int myNode){

  for(int pDeg=0;pDeg<degreeP;pDeg++){
    P[Pshift*pDeg+myNode] = ploc[pDeg];
  }//pDeg

}//sendDataUK


#endif //__SUMFORCE_H__
