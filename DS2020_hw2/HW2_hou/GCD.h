// 
// Gcd.h
// DS hw2 array gcd
//

#ifndef _GCD_
#define _GCD_
#define ARRAY_MAX 1000
using namespace std;
class GCD {
	private:

	public:
	GCD(){}
	~GCD(){}
	long* FindGCD(long *in1,long *in2,int deg1,int deg2);
};

class Poly {
  private:

  public:
    Poly(){}
    ~Poly(){}
    Poly reduce();
    Poly transform(long *d);
    Poly new_term(int e,__int128_t c);
    Poly operator+(const Poly& b);
    Poly operator-(const Poly& b);
    Poly operator*(const Poly& b);
    Poly operator%(const Poly& b);
};
#endif

