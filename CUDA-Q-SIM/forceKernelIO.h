#ifndef __FORCEKERNELIO_H__
#define __FORCEKERNELIO_H__

#include "parameters.h"

///////////////////////////////
//read data INTO local thread//
///////////////////////////////
__device__ void getDataFK(float (&Ploc)[4*degreeP]
                         ,float (&Ainv)[16]
                         ,float *A
                         ,int Ashift
                         ,int *TetNodeRankG 
                         ,int (&TetNodeRank)[4]
                         ,int *TetToNode
                         ,int TTNshift
                         ,int Ntets 
                         ,int (&node_num)[4]){
	
	int mynode;
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
			for(int n = 0;n<4;n++){

				//figure out what 4 nodes make up tetrahedra
				mynode = TetToNode[TTNshift*n+tid];
				node_num[n] = mynode;
				TetNodeRank[n] = TetNodeRankG[tid + Ntets*n];
				for(int cord = 0;cord<4;cord++){
  				Ainv[cord+n*4] = A[Ashift*(cord+n*4)+tid];
				}//cord 
        //read in P data for each node
        for(int pDeg=0;pDeg<degreeP;pDeg++){
          Ploc[n+pDeg*4] = tex2D(texRef_P,mynode,pDeg);
        }//pDeg
			}//n
	
}//getDataFK

///////////////////////////////
//send data from Local thread//
///////////////////////////////
__device__ void sendDataFK(float *fP
                          ,int fPshift
                          ,float fPloc[4*degreeP]
                          ,int node_num[4]
                          ,int TetNodeRank[4]
                          ,float myVol){

  int n_glob,NodeRank;
  //loop over tetrahedron
  for(int n=0;n<4;n++){
    //loop over degree of freedom
    for(int pDeg=0;pDeg<degreeP;pDeg++){
      fP[fPshift*(degreeP*NodeRank+pDeg)+n_glob]=fPloc[n+pDeg*4];
    }//pDeg
  }//n

}//sentDataFK
#endif//__FORCEKERNELIO_H__

