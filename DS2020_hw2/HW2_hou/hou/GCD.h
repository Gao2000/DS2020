// 
// Gcd.h
// DS hw2 array gcd
//

#ifndef _GCD_
#define _GCD_
#define ARRAY_MAX 1000

using namespace std;


class Poly
{
friend class GCD;
private:	
	class Term
	{
	public:
		__int128_t coef;
		int exp;
		Term(){ coef=0; exp=0; }
	};
	Term *t_array;
	int capacity;
	int terms;
public:
	Poly(){ capacity=1; terms=0; t_array=new Term[1]; }
	~Poly(){ }
	Poly operator+(const Poly&);
	Poly operator-(const Poly&);
	Poly operator*(const Poly&);
	Poly operator%(const Poly&);
	Poly new_term(int,__int128_t);
	Poly transform(long*);
	Poly reduce();
};

class GCD
{
private:
	Poly p1,p2;	
public:
	GCD(){}
	~GCD(){}
	long* FindGCD(long *in1,long *in2, int, int);
	long* to_long(const Poly&);
};
#endif

