//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"

bool isPrime(unsigned long n) {
  for(unsigned long j = 2; (j * j) <= n; j++) {
    if(n % j == 0) return false;
  }
  return true;
}
unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b) {
  unsigned long prime_num = 0;
  
  for(; a <= b; a++) {
    if(isPrime(a)) prime_num++; //check the number is prime or not
  }
	
	return prime_num; //return the prime_num's qutantity
}
