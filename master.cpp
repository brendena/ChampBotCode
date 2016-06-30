#include "master.h"

int Master::minParametersMaped = 0;
int Master::maxParametersMaped = 100;

int Master::changeRange(int x){
  return map(x,1055, 1900,minParametersMaped, maxParametersMaped);
  
  //map(value, fromLow, fromHigh,toLow, toHigh)
    
}

bool Master::marginError(int postion, int marginError){
  return ( (postion <= marginError) && (postion >= -marginError) );
}  



