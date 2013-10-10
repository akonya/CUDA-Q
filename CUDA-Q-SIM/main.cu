//=============================================================//
//                                                             //
//                      || CUDA-Q ||                           //
//                                                             //
//              --------Version 1.0----------                  //
//                                                             //
//                                                             //
//                                                             //
//    Authors: Andrew Konya      (Kent State University)       //
//             Jonathan Selinger (Kent State University)       // 
//                                                             //
//=============================================================//


#include "mainhead.h"






int main()
{

	
	//Get Device properties
	cudaDeviceProp prop;
	HANDLE_ERROR(cudaGetDeviceProperties(&prop,0));
	printf( "Code executing on %s\n\n", prop.name );
	//displayGPUinfo(prop);

	int Ntets,Nnodes;
	//get dimensions of the mesh
	get_mesh_dim(Ntets,Nnodes);
	
	//create objects of TetArray and NodeArray class with correct size
	TetArray Tet = TetArray(Ntets);
	NodeArray Node = NodeArray(Nnodes);

	//read the mesh into Node and Tet objects
	get_mesh(Node,Tet,Ntets,Nnodes);

	//get positions of tetrahedra
	get_tet_pos(Node,Tet,Ntets);

	//reorder tetrahedra 
	gorder_tet(Node,Tet,Ntets);

	//re-order nodes and reassing tetrahedra component lists
	finish_order(Node,Tet,Ntets,Nnodes);

	//find initial A's and invert them  store all in Tet object
	init_As(Node,Tet,Ntets);

	//now ready to prepare for dyanmics
	//delcare data stuctures for data on device
	//and host
	DevDataBlock dev_dat;
	HostDataBlock host_dat;

	//Pack data to send to device
	packdata(Node,Tet,&host_dat,Ntets,Nnodes);

	//send data to device
	data_to_device(&dev_dat,&host_dat,Ntets,Nnodes);


	//=================================================================
	//run dynamics
	//=================================================================

	//run_dynamics(&dev_dat,&host_dat,Ntets,Nnodes);

	//check for CUDA erros
	any_errors();

	//exit program
	exit_program(&dev_dat);

  return 0;
}
