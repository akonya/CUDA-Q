#ifndef __UPDATAKERNEL_H__
#define __UPDATAKERNEL_H__

#include "updateKernelIO.h"
#include "updateCalc.h"
#include "parameters.h"

//================================================
// -read in all forces on each node and sum them
// -use velocity verilet to step system forward
// -send updated positions to global memory 
//================================================
__global__ void updateKernel(	 float *fP
								,int pitchfP
								,float *P
								,int pitchP
								,int Nnodes 
								,int *NodeRank){
	
	int fPshift = pitchfP/sizeof(float);
	int Pshift = pitchP/sizeof(float);
	int myNode;
	int myNodeRank;
	float fPloc[degreeP]={0.0};
  float ploc[degreeP]={0.0};
	//thread ID
	int tid = threadIdx.x + blockIdx.x * blockDim.x;


	if (tid<Nnodes){  //if a node is here
		myNode=tid;
		myNodeRank = NodeRank[myNode];
    

    //get effective force Data
    getDataUK(  myNode
              , myNodeRank
              , fPloc
              , fP
              , fPshift
              , P
              , Pshift
              , ploc);

    //calculate new P's
    calcP( ploc, fPloc);

		//send newly calculated P's
		sendDataUK( ploc
              , P
              , Pshift
              , myNode); 
    		

	}//tid<Nnodes




}//updateKernel


#endif//__UPDATAKERNEL_H__
