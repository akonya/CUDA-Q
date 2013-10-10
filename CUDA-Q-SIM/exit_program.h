#ifndef __EXIT_PROGRAM_H__
#define __EXIT_PROGRAM_H__


void exit_program(DevDataBlock *dev_dat){
cudaUnbindTexture( texRef_P );



HANDLE_ERROR( cudaFree( dev_dat->dev_A ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_TetToNode ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_nodeRank ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_TetNodeRank ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_pe ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_TetVol ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_P ) );
HANDLE_ERROR( cudaFree( dev_dat->dev_fP ) );
}



#endif//__EXIT_PROGRAM_H__
