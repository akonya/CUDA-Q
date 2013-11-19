#ifndef __RUNDYNAMICS_H__
#define __RUNDYNAMICS_H__
#include "mainhead.h"
#include "parameters.h"
#include "forceKernel.h"
#include "updateKernel.h"



//This funciton handles all dynamics which will be run
void run_dynamics(DevDataBlock *data
					, HostDataBlock *host_data
					, int Ntets
					, int Nnodes){


	//=================================================================
	//claclulate number of blocks to be executed
	//=================================================================
	cudaDeviceProp dev_prop;
	HANDLE_ERROR(cudaGetDeviceProperties(&dev_prop,0));
	int Threads_Per_Block = TPB;
	int BlocksTet = (Ntets+Threads_Per_Block)/Threads_Per_Block;
	int BlocksNode = (Nnodes+Threads_Per_Block)/Threads_Per_Block;

  //================================================================
	// create start and stop events to measure performance
	//================================================================
	cudaEvent_t startF, stopF, startU, stopU; 
	float elapsedTimeF,elapsedTimeU;
	float etF = 0.0, etU = 0.0;
  float countF = 0.0, countU = 0.0;



	//================================================================
	// Begin Dynamics
	//================================================================

	for(int iKern=0;iKern<NSTEPS;iKern++){
	  
     //timer for force calculation
	  HANDLE_ERROR(cudaEventCreate(&startF));
	  HANDLE_ERROR(cudaEventCreate(&stopF));
	  HANDLE_ERROR(cudaEventRecord(startF,0));

  	//calculate force and send force components to be summed
	  force_kernel<<<BlocksTet,Threads_Per_Block>>>( data->dev_A
											  , data->dev_Apitch
											  , data->dev_P
											  , data->dev_Ppitch
                        , data->dev_fP
                        , data->dev_fPpitch
											  , data->dev_TetNodeRank
											  , Ntets 
											  , data->dev_pe
											  , data->dev_TetVol
											  , data->dev_TetToNode
											  , data->dev_TetToNodepitch
											  , dt*float(iKern));

	  //sync threads before updating
	  cudaThreadSynchronize();
    
	  //end timer for force kernel
	  HANDLE_ERROR(cudaEventRecord(stopF, 0));
	  HANDLE_ERROR(cudaEventSynchronize(stopF));
  	HANDLE_ERROR(cudaEventElapsedTime(&elapsedTimeF, startF, stopF));
	  HANDLE_ERROR( cudaEventDestroy( startF ));
	  HANDLE_ERROR( cudaEventDestroy( stopF ));

    //start timer for update routine	
    HANDLE_ERROR(cudaEventCreate(&startU));
	  HANDLE_ERROR(cudaEventCreate(&stopU));
	  HANDLE_ERROR(cudaEventRecord(startU,0));

	  //sum forces and update positions
	  updateKernel<<<BlocksNode,Threads_Per_Block>>>( data->dev_fP
												, data->dev_fPpitch
												, data->dev_P
												, data->dev_Ppitch
												, Nnodes
												, data->dev_nodeRank);

	  //sync threads before updating
	  cudaThreadSynchronize();

	  //end timer for update kernel
  	HANDLE_ERROR(cudaEventRecord(stopU, 0));
	  HANDLE_ERROR(cudaEventSynchronize(stopU));
	  HANDLE_ERROR(cudaEventElapsedTime(&elapsedTimeU, startU, stopU));
	  HANDLE_ERROR( cudaEventDestroy( startU ));
	  HANDLE_ERROR( cudaEventDestroy( stopU ));

    //update timer data
    etF += elapsedTimeF;
    etU += elapsedTimeU;
    countF += 1.0;
    countU += 1.0;

    //Tasks to cary out each frame 
		if((iKern)%iterPerFrame==0){

  		//print calculation speed
	  	printf("\n forceKernel = %f ms |  updateKernel = %f ms\n"
                ,elapsedTimeF
                ,elapsedTimeU);
      printf(" %d of %d complete\n"
                ,iKern+1
                ,NSTEPS);

  	}//if((iKern+1)%iterPerFrame==0)


  }//iKern

  FILE*pout;
  pout = fopen("Performance//timing.dat","w");
  fprintf(pout,"nodes = %d\n",Nnodes);
  fprintf(pout,"elements = %d\n",Ntets);
  fprintf(pout,"forcecalc time (ms) = %f\n",etF/countF);	
  fprintf(pout,"update time (ms) = %f\n",etU/countU);
  fclose(pout);	

};

#endif
