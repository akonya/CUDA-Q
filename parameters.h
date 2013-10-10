#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

//standard simulation parameters
#define NSTEPS			100000					    //total number of iterations
#define dt              0.000001					    //timestep [s]
#define iterPerFrame    5000                            //iterations per printed frame

//meshfile
#define MESHFILE "Mesh//beam400_50_50_n277_e734_f508.dat"

//convert mesh length scale to cm
#define meshScale        0.1         //--[ cm / mesh unit]                      

//define # of degress of freedom to simulate
#define degreeP          5           // 5 for Q tensor sim

//Threads per block to exicute
//100 seems pretty optimal on GTX275
//might be better with larger on 
//better card/ differnt card
#define TPB				100			



//maximum number of tetrahedra
//a Node can belone to
#define MaxNodeRank     90							



//constants declared on the stack for speed
#define PI				3.14159265359
#define dt2o2           (dt*dt)/2.0					    //for speed
#define dto2             dt/2.0						    //for speed

#endif //__PARAMETERS_H__
