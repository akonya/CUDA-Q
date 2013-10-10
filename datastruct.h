#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

struct DevDataBlock {
	float *dev_A;
	int *dev_TetToNode;
	int *dev_nodeRank;
	int *dev_TetNodeRank;
	float *dev_pe;
	float *dev_TetVol;
  float *dev_P;
  float *dev_fP;
	size_t dev_Apitch;
	size_t dev_TetToNodepitch;
  size_t dev_Ppitch;
  size_t dev_fPpitch;

	cudaEvent_t     start, stop;
    float           totalTime;
};

struct HostDataBlock {
	float *host_A;
	int *host_TetToNode;
	int *host_nodeRank;
	int *host_TetNodeRank;
	float *host_pe;
	float host_totalVolume;
	float *host_TetVol;
  float *host_P;
  float *host_fP;
};


#endif //__DATASTRUCT_H__
