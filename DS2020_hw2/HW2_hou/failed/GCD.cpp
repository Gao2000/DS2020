//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

//gcd of int128
__int128_t gcd(__int128_t a, __int128_t b){
  if(a && b){
    while(a && b)
      if(a + b)
        return a + b;
  }
  return 1;
}
//abs of int128
__int128_t llabs(__int128_t a){
  if(a > 0)
    return a;
  return (-a);
}

/* --------------------------------------------------
 * ----------------GCD part--------------------------
 * -------------------------------------------------- */

long* GCD::FindGCD(long *in1,long *in2,int deg1,int deg2){
  Poly p1, p2;
  p1.transform(in1, deg1);
  p2.transform(in2, deg2);
  p1.reduce();
  p2.reduce();
  
  Poly temp;
  while(p2.n != 0){
    temp = p1 % p2;
    p1 = p2;
    p2 = temp;
    p1.reduce();
    p2.reduce();
  }

  p1.reduce();

  return to_long(p1);
}

//transform __int128_t to long type
long* GCD::to_long(const Poly& a){
  long *ans = new long[ARRAY_MAX];

  for(int i = 0; i < ARRAY_MAX; i++)
    ans[i] = 0;

  for(int i = 0; i <= a.n; i++)
    ans[i] = a.p_array[i];
  
  return ans;
}

/* --------------------------------------------------
 * ----------------Poly part-------------------------
 * -------------------------------------------------- */

Poly Poly::reduce(){
  if(n == 0)
    return *this;
  //the first term
  __int128_t t = llabs(p_array[n]);
  //find the gcd of all terms
  for(int i = n - 1; i >= 0; i--)
    if(p_array[i] != 0)
      t = gcd(t, llabs(p_array[i]));
  //keep the first term is positive
  if(p_array[n] < 0)
    t = -llabs(t);
  //simplest all terms
  if(t != 1 && t != 0)
    for(int i = 0; i <= n; i++)
      p_array[i] /= t;

  return *this;
}

Poly Poly::transform(long *d, int deg){
  n = deg;
  //create a ARRAY_MAX size of __int128_t array
  for(int i = 0; i < ARRAY_MAX; i++)
    p_array[i] = 0;
  
  for(int i = 0; i <= n; i++)
    p_array[i] = d[i];

  return * this;
}

Poly Poly::operator+(const Poly& b){
  Poly ans;
  for(int i = 0; i < ARRAY_MAX; i++)
    ans.p_array[i] = 0;

  for(int i = 0; i <= n || i <= b.n; i++)
    ans.p_array[i] = p_array[i] + b.p_array[i];

  return ans;
}

Poly Poly::operator-(const Poly& b){
  Poly ans;
  for(int i = 0; i < ARRAY_MAX; i++)
    ans.p_array[i] = 0;

  for(int i = 0; i <= n || i <= b.n; i++)
    ans.p_array[i] = p_array[i] - b.p_array[i];
  
  return ans;
}

void Poly::check_changes(){
  int temp = n;
  while(temp >= 0){
    if(p_array[temp] == 0)
      temp--;
    else
      break;
  }
  n = temp;
  return;
}

Poly Poly::operator%(const Poly& b){
  //initial div
  Poly div;
  div.n = n;
  for(int i = 0; i < ARRAY_MAX; i++)
    div.p_array[i] = 0;

  for(int i = 0; i <= div.n; i++)
    div.p_array[i] = p_array[i];

  //initial temp 
  Poly temp;
  temp.n = 0;
  
  int mul_e;
  int cur_deg = div.n, max_deg = b.n;

  while(div.n >= 0 && cur_deg >= max_deg){
    div.reduce();
    mul_e = div.n - b.n;

    __int128_t mul_div = b.p_array[b.n] / gcd(div.p_array[div.n], b.p_array[b.n]);
    __int128_t mul_b = div.p_array[div.n] / gcd(div.p_array[div.n], b.p_array[b.n]);

    temp.n = b.n;

    for(int i = 0; i < ARRAY_MAX; i++)
      temp.p_array[i] = b.p_array[i];
    
    for(int i = 0; i < div.n; i++)
      div.p_array[i] *= mul_div;

    //temp shift mul_e
     __int128_t tmp[ARRAY_MAX] = {0};
    for(int j = 0; j <= temp.n; j++) 
      tmp[j] = temp.p_array[j];
    for(int j = 0; j <= temp.n; j++)
       tmp[j] = 0;
     for(int j = 0; j <= temp.n; j++)
       temp.p_array[j+mul_e] = tmp[j];
     temp.n += mul_e;

    for(int i = 0; i <= div.n; i++)
      temp.p_array[i] *= mul_b;
    
    div = div - temp;

    div.reduce();
    div.check_changes();
    if(div.n == -1)
      break;
  }
  return div;
}
