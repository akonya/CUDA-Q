#ifndef __QLIB_H__
#define __QLIB_H__

#include "jacobi_cycle.h"

//////////////////////////////////////
//Get 3x3 Q tensor from 5x1 P tensor
//////////////////////////////////////
void QfromP(float (&P)[5],float (&Q)[9]){
  float c1 = 0.4082482904638631; // 1/sqrt(6)
  float c2 = 0.7071067811865475; // 1/sqrt(2)

  //Q_jk    indexed by Q[3*j+k]
  //T^i_jk   indexed by T[9*i+3*j+k]

  float T[45]={-c1,0.,0.,0.,c1,0.,0.,0.,2.0*c1 \
               ,c2,0.,0.,0.,-c2,0.,0.,0.,0. \
               ,0.,c2,0.,c2,0.,0.,0.,0.,0. \
               ,0.,0.,c2,0.,0.,0.,c2,0.,0. \
               ,0.,0.,0.,0.,0.,c2,0.,c2,0.};

  //zero out Q
  for(int i=0;i<9;i++){Q[i]=0.0;}

  //construct Q_jk = P_i T_ijk
  for(int i=0;i<5;i++){
    for(int j=0;j<3;j++){
      for(int k=0;k<3;k++){
        Q[3*j+k] += T[9*i+3*j+k];
      }//k
    }//j
  }//i

}//QfromP 


//////////////////////////////////////
//  get director n  (3x1)
//  and order parameter S 
//  from Q-tensor
//////////////////////////////////////
void NSfromQ(float (&Q)[9],float (&n)[3], float S){

  //get Q in form for jacobi cycle
  double Qd[3][3];
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      Qd[i][j] = double(Q[3*i+j]);
    }//j
  }//i

  //get eigen values/vectors for Qd
  double eigenvectors[3][3];
  double eigenvalues[3];

  Jacobi_Cyclic_Method( eigenvalues
                      , (double*)eigenvectors
                      , (double*) Qd
                      , 3);

  //find maximum eigenvalue
  double maxVal = eigenvalues[0];
  int maxLoc = 0;
  for(int i=1;i<3;i++){
    if(maxVal<eigenvalues[i]){
      maxVal = eigenvalues[i];
      maxLoc = i;
    }//if
  }//i

  //Set order parameter
  S = float(maxVal);
  
  //get n
  n[0] = float(eigenvectors[0][maxLoc]);
  n[1] = float(eigenvectors[1][maxLoc]);
  n[2] = float(eigenvectors[2][maxLoc]);

}//NSfromQ



#endif //__QLIB_H__
