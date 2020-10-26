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
    long ans[1000] = {0};
    int deg_ans;
	public:
	GCD(){}
	~GCD(){}
	long* FindGCD(long *in1,long *in2,int deg1,int deg2);
  friend void do_div(long*, long*, int, int);
};
#endif

