//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"
#include <cmath>
#include <iostream>

unsigned long long_gcd(unsigned long i, unsigned long j);
void simplest(long *in1, int deg1);
bool check_zero(long in1[], int deg1);
int check_changes(long in1[], int deg1);

long* GCD::FindGCD(long *in1,long *in2,int deg1,int deg2){
  //in1's degree need to biger than in2
  for(int i = 0; i < 1000; i++)
    ans[i] = 0;
  long* tmp; int temp;
  if(deg1 < deg2){
    tmp = in2;
    in2 = in1;
    in1 = tmp;

    temp = deg1;
    deg1 = deg2;
    deg2 = temp;
  }
  do_div(in1, in2, deg1, deg2);
  long *re_ans = new long[1000];
  for(int i = 0; i < 1000; i++)
    re_ans[i] = ans[i];
	return re_ans;
}

//Eculidean algorithim in1 = q * in2 + r
void GCD::do_div(long *in1, long *in2, int deg1, int deg2){
  int i = 0;
  long q[1000] = {0}; long r[1000] = {0};
  int deg_q, deg_r;
  deg_q = deg1 - deg2;
  deg_r = deg1 - 1;

  if(check_zero(in2, deg2)){
    cout << "wrong in2 is zero\n";
    this->ans[0] = 1;
    return;
  }

  while(i <= deg_q){
    simplest(in1, deg1); simplest(in2, deg2);

    //keep in1[deg1] % in2[deg2] = 0
    if(in1[deg1] % in2[deg2] != 0){
      long lcm_first_term = (in2[deg2] / long_gcd(in1[deg1], in2[deg2]));
      for(int j = 0; j <= deg1; j++)
        in1[j] *= lcm_first_term;
    }

    deg_r = deg1 - 1;
    q[deg_q - i] = in1[deg1] / in2[deg2];
    long tmp = q[deg_q - i];

    for(int j = deg_r; j >= 0; j--){
      if(j >= deg_q - i)
        r[j] = in1[j] - tmp * in2[j - deg_q + i];
      else
        r[j] = in1[j];
    }

    if(check_zero(r, deg_r)) break;
    //in1 = r
    for(int j = 0; j <= deg1; j++)
      in1[j] = r[j];
    deg1 = deg_r;
    //
    i++;
  }

  deg_r = check_changes(r, deg_r);
  if(deg_r == -1){
    deg2 = check_changes(in2,deg2);
    simplest(in2, deg2);
    for(int j = 0; j <= deg2; j++)
      this->ans[j] = in2[j];
    return;
  }
  else{
    do_div(in2, r, deg2, deg_r);
  }
}

unsigned long long_gcd(unsigned long i, unsigned long j){
  int shift = 0;

  //GCD(0,j) == j, GCD(i,0) == i, GCD(0,0) == 0
  if(i == 0) return j;
  if(j == 0) return i;

  //Let shift := lg K, where K is the greatest power of 2 dividing both i and j.
  while(((i | j) & 1) == 0){
    shift++;
    i >>= 1;
    j >>= 1;
  }

  while((i & 1) == 0)
    i >>= 1;

  //From here on, i is always odd.
  do{
    //remove all factor of 2 in v-- they are not common
    //note: v is not zero, so while will terminate
    while((j & 1) == 0)
      j >>= 1;

    /*Now i and j are both odd. Swap if necssary so i <= j, then set j = j - i
     * (which is even). For bignums, the swapping is just pointer movement, and
     * the subtraction can be done in-place
     */
    if(i > j){
      int t = i; i = j; j = t; //Swap i and j
    }

    j -= i; //Here j >= i
  }while(j != 0);

  //restore common factors of 2
  return i << shift;
}

void simplest(long *in1, int deg1){
  //let first term be postive
  if(in1[deg1] < 0)
    for(int i = deg1; i >= 0; i--)
      in1[i] *= -1;
  //find the GCD(f) of all nonzero terms
  long f = in1[deg1];
  for(int i = deg1 - 1; i >= 0; i--)
    if(in1[i] != 0)
      f = long_gcd(abs(f), abs(in1[i]));
  //all terms /= f
  for(int i = deg1; i >= 0; i--)
    in1[i] /= f;
}
//cheack the in1 is nonzero
bool check_zero(long in1[], int deg1){
  for(int i = deg1; i >= 0; i--)
    if(in1[i] != 0)
      return false;
  return true;
}
//cheack the changes of in1's degree
int check_changes(long in1[], int deg1){
  while((in1[deg1] == 0) && (deg1 >= 0))
    deg1--;
  return deg1;
}
