// 
// Gcd.h
// DS hw2 array gcd
//

#ifndef _GCD_
#define _GCD_
#define ARRAY_MAX 1000
using namespace std;
class Poly {
  private:
    __int128_t p_array[ARRAY_MAX];
    int n;
  public:
    Poly(){}
    ~Poly(){}
    Poly reduce();
    Poly transform(long *d, int deg);
    //Poly new_term(int e,__int128_t c);
    Poly operator+(const Poly& b);
    Poly operator-(const Poly& b);
    //Poly operator*(const Poly& b);
    Poly operator%(const Poly& b);
    void check_changes();
    friend class GCD;
};

class GCD {
	private:
	public:
	GCD(){}
	~GCD(){}
	long* FindGCD(long *in1,long *in2,int deg1,int deg2);
  long* to_long(const Poly& a);
};

#endif

