#ifndef __DATATODEVICE_H__
#define __DATATODEVICE_H__

#include "mainhead.h"

void data_to_device(DevDataBlock *dev_dat, HostDataBlock *host_dat,int Ntets,int Nnodes){


	//need to pitch 1D memory correctly to send to device
	size_t height16 = 16;
	size_t height4 = 4;
	size_t heightMR = MaxNodeRank*degreeP;
  size_t degP = degreeP;
	size_t widthNODE = Nnodes;
	size_t widthTETS = Ntets;

	//set offset to be 0
	size_t offset = 0;



	//used pitch linear memory on device for fast access
	//allocate memory on device for pitched linear memory

	HANDLE_ERROR( cudaMallocPitch( (void**) &dev_dat->dev_A 
									, &dev_dat->dev_Apitch 
									, widthTETS*sizeof(float) 
									, height16 ) );

	HANDLE_ERROR( cudaMallocPitch( (void**) &dev_dat->dev_fP 
									, &dev_dat->dev_fPpitch 
									, widthNODE*sizeof(float) 
									, heightMR ) );

	HANDLE_ERROR( cudaMallocPitch( (void**) &dev_dat->dev_TetToNode 
									, &dev_dat->dev_TetToNodepitch 
									, widthTETS*sizeof(float) 
									, height4 ) );
		

	HANDLE_ERROR( cudaMallocPitch( (void**) &dev_dat->dev_P 
									, &dev_dat->dev_Ppitch  
									, widthNODE*sizeof(float) 
									, degP ) );
	HANDLE_ERROR( cudaMalloc( (void**) &dev_dat->dev_TetNodeRank
									,Ntets*4*sizeof(int) ) );

	HANDLE_ERROR( cudaMalloc( (void**) &dev_dat->dev_nodeRank
									,Nnodes*sizeof(int) ) );

	HANDLE_ERROR( cudaMalloc( (void**) &dev_dat->dev_pe
									,Ntets*sizeof(float) ) );
	
	HANDLE_ERROR( cudaMalloc( (void**) &dev_dat->dev_TetVol
									,Ntets*sizeof(float) ) );
	
	//copy data to device
	//This will copy each 1D array as if it 
	//is a pitched linear array which can be accessed like
	//a 2-D array

	HANDLE_ERROR( cudaMemcpy(dev_dat->dev_TetNodeRank
								,host_dat->host_TetNodeRank
								,Ntets*4*sizeof(int)
								,cudaMemcpyHostToDevice) );

	HANDLE_ERROR( cudaMemcpy(dev_dat->dev_nodeRank
								,host_dat->host_nodeRank
								,Nnodes*sizeof(int)
								,cudaMemcpyHostToDevice) );

	HANDLE_ERROR( cudaMemcpy(dev_dat->dev_TetVol
								,host_dat->host_TetVol
								,Ntets*sizeof(float)
								,cudaMemcpyHostToDevice) );

	HANDLE_ERROR( cudaMemcpy2D( dev_dat->dev_A
								, dev_dat->dev_Apitch
								, host_dat->host_A
								, widthTETS*sizeof(float)
								, widthTETS*sizeof(float)
                                , height16
								, cudaMemcpyHostToDevice ) );

	HANDLE_ERROR( cudaMemcpy2D( dev_dat->dev_TetToNode
								, dev_dat->dev_TetToNodepitch
								, host_dat->host_TetToNode
								, widthTETS*sizeof(int)
								, widthTETS*sizeof(int)
								, height4
								, cudaMemcpyHostToDevice ) );

	HANDLE_ERROR( cudaMemcpy2D( dev_dat->dev_P
								, dev_dat->dev_Ppitch
								, host_dat->host_P
								, widthNODE*sizeof(float)
								, widthNODE*sizeof(float)
								, degP
								, cudaMemcpyHostToDevice ) );

	HANDLE_ERROR( cudaMemcpy2D( dev_dat->dev_fP
								, dev_dat->dev_fPpitch
								, host_dat->host_fP
								, widthNODE*sizeof(float)
								, widthNODE*sizeof(float)
								, heightMR
								, cudaMemcpyHostToDevice ) );


	//================================================
	//bind linear pitched memory to 2D texture
	//================================================


	HANDLE_ERROR( cudaBindTexture2D( &offset 
									,texRef_P
									, dev_dat->dev_P
									, texRef_P.channelDesc
									, widthNODE
									, degP
									, dev_dat->dev_Ppitch) );
	texRef_P.normalized = false;
	//texRef_r0.filterMode = cudaFilterModeLinear;




	printf("\ndata sent to device\n");

}


#endif//__DATATODEVICE_H__
