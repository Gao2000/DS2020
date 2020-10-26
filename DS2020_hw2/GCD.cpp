//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"
#include <cmath>
#include <iostream>

//Eculidean algorithim in1 = q * in2 + r
void do_div(long *in1, long *in2, int deg1, int deg2){
  int i = 0, j;
  long q[1000] = {0}; long r[1000] = {0};
  int deg_q, deg_r;
  deg_q = deg1 - deg2;
  deg_r = deg1 - 1;
  
  //if in1's degree need to biger than in2
  long* tmp;
  if(deg1 < deg2){
    tmp = in2;
    in2 = in1;
    in1 = temp;
  }

  if(check_zero(in2, deg2)){
    cout << "wrong in2 is zero\n";
    exit(0);
  }
 
  simplest(in1); simplest(in2);
  while(i <= deg_n){
  
  }
}

long* GCD::FindGCD(long *in1,long *in2,int deg1,int deg2){
  do_div(in1, in2, deg1, deg2);	
	return this.ans;
}

