//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"
#include <cmath>

unsigned long long pow_mod(unsigned long x, unsigned long n, unsigned long mod) {
  unsigned long long res = 1;
  x = x % mod;
  while(n){
    if(n & 1) res = res * x % mod;
    x = x * x % mod;
    n >>= 1; // y = y/2
  }
  return res;
}

bool isPrimeBasic(unsigned long n) {
  for(unsigned long j = 2; (j * j) <= n; j++) {
    if(n % j == 0) return false;
  }
  return true;
}

bool isPrime(unsigned long n) {
  //check the num isn't even
  if(n == 2) return true;
  if(n < 2 || n % 2 == 0) return false;
  
  unsigned long u = n - 1, t = 0;
  while(u % 2 == 0) { u >>= 1; t++;}

  //unsigned long long sprp[3] = {2, 7, 61};
  unsigned long long sprp[3] = {2, 379215, 457083754};
  for(int k = 0; k < 3; ++k) {
    unsigned long long a = sprp[k] % n;
    if(a == 0 || a == 1 || a == n - 1) continue;

    unsigned long long x = pow_mod(a, u, n);
    if(x == 1 || x == n - 1) continue;

    for(unsigned long i = 0; i < t - 1; i++) {
      x = (x * x) % n;
      if(x == 1) return false;
      if(x == n - 1) break;
    }
    if(x == n - 1) continue;

    return false;
  }
  return true;
}

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b) {
  unsigned long prime_num = 0;
  
  for(; a <= b; a++) {
    if(a >= 4294967296) {
      if(isPrimeBasic(a)) prime_num++;
      continue;
    } 
    if(isPrime(a)) prime_num++; //check the number is prime or not
  }
	
	return prime_num; //return the prime_num's qutantity
}
