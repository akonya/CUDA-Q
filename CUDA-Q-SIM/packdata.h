#ifndef __PACKDATA_H__
#define __PACKDATA_H__
#include "parameters.h"
#include <math.h>


//this function takes all the data about the simulatin and 
//packs it in a way that will make it easy to copy to GPU
void packdata(NodeArray &i_Node,TetArray &i_Tet, HostDataBlock *dat,int Ntets,int Nnodes){

	//allocate memory on host
	dat->host_A = (float*)malloc(Ntets*16*(sizeof(float)));
	dat->host_TetToNode = (int*)malloc(Ntets*4*(sizeof(int)));
	dat->host_nodeRank = (int*)malloc(Nnodes*sizeof(int));
	dat->host_pe = (float*)malloc(Ntets*sizeof(float));
	dat->host_TetNodeRank = (int*)malloc(Ntets*4*sizeof(int));
	dat->host_totalVolume = i_Tet.get_total_volume();
	dat->host_TetVol = (float*)malloc(Ntets*sizeof(float));
  dat->host_fP = (float*)malloc(Nnodes*MaxNodeRank*sizeof(float));
  dat->host_P = (float*)malloc(Nnodes*degreeP*sizeof(float));

	for (int tet = 0;tet<Ntets;tet++){
		dat->host_TetVol[tet] = i_Tet.get_volume(tet);
    dat->host_pe[tet] = 0.0;
		for (int sweep = 0;sweep<4;sweep++){
				dat->host_TetToNode[tet+sweep*Ntets] = i_Tet.get_nab(tet,sweep);
				dat->host_TetNodeRank[tet+sweep*Ntets] = i_Tet.get_nabRank(tet,sweep);

			//pack A inverted matrix
				for(int sweep2 = 0;sweep2<4;sweep2++){
			     dat->host_A[tet+(4*sweep+sweep2)*Ntets] = i_Tet.get_invA(tet,sweep,sweep2);
				}
		}//sweep
	}//tet

	for(int nod = 0;nod<Nnodes;nod++){
		dat->host_nodeRank[nod] = i_Node.get_totalRank(nod);
    for(int rk=0;rk<MaxNodeRank;rk++){
      dat->host_fP[nod*MaxNodeRank+rk] = 0.0;
    }//rk
    for(int deg=0;deg<degreeP;deg++){
      dat->host_fP[nod*degreeP+deg] = 0.0;
    }//rk
	}//nod

	printf("Data packed to go to device\n");
}


#endif //__PACKDATA_H__
