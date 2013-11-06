#ifndef __FORCEKERNEL_H__
#define __FORCEKERNEL_H__
#include "mainhead.h"
#include "forceKernelIO.h"


__global__ void force_kernel(	float *A
								,int pitchA
								,float *fP
                ,int pitchfP
								,int *TetNodeRankG
								,int Ntets
								,float *pe
								,float *TetVol
								,int *TetToNode
								,int pitchTetToNode
								,float t){


	int Ashift = pitchA/sizeof(float);
	int fPshift = pitchfP/sizeof(float);
	int TTNshift = pitchTetToNode/sizeof(int);
	float Ainv[16];
  float Ploc[4*degreeP];
  float fPloc[4*degreeP] = {0.0};
	int node_num[4];
	int TetNodeRank[4];
	float myVol;

	


	//thread ID
	int tid = threadIdx.x + blockIdx.x * blockDim.x;


	if(tid<Ntets){ //if thread executed has a tetrahedra


		//read in all data needed to do force calc
		myVol = TetVol[tid];   //simple enough here
    getDataFK(Ploc
             ,Ainv
             ,A
             ,Ashift
             ,TetNodeRankG
             ,TetNodeRank
             ,TetToNode
             ,TTNshift
             ,Ntets
             ,node_num);                  

		//calculate effective force on each DOF
    force_calc(Ainv,Ploc,fPloc,myVol);


		//send data, local force components, to global memory 
    sendDataFK(fP
              ,fPshift
              ,fPloc
              ,node_num
              ,TetNodeRank
              ,myVol);

	}//end if tid<Ntets

}//end force kernel


#endif // __GPUFORCE_H__

