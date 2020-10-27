//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;
 
__int128_t gcd(__int128_t a,__int128_t b)
{
	if(a && b){
		while((a%=b)&&(b%=a));
		if(a+b)
			return a+b;
	}
	return 1;
}

__int128_t llabs(__int128_t a)
{
	if(a>0)
		return a;
	return (-a);
}
Poly Poly::reduce()
{
	if(terms==0)
		return *this;
	__int128_t t=llabs(t_array[0].coef);
        for(int i=0;i<terms;i++){
                t=gcd(t,llabs(t_array[i].coef));
        }
        if(t_array[terms-1].coef<0)
                t=-llabs(t);
        if(t!=1&&t!=0){
                for(int i=0;i<terms;i++){
                        t_array[i].coef/=t;
                }
        }
	return *this;
}
long* GCD::FindGCD(long *in1,long *in2){
	
	static int s=0;
	s++;
  p1.transform(in1);	
	p2.transform(in2);
	p1.reduce();
	p2.reduce();
	Poly temp;
	while(p2.terms!=0){
		temp=p1%p2;
		p1=p2;
		p2=temp;
		p1.reduce();
		p2.reduce();
	}
	
	p1.reduce();

	return to_long(p1);
}

long* GCD::to_long(const Poly& a)
{
	long *ans=new long[ARRAY_MAX];
	
	for(int i=0;i<ARRAY_MAX;i++)
		ans[i]=0;
	for(int i=0;i<a.terms;i++){
		ans[(a.t_array[i].exp)]=a.t_array[i].coef;
	}
	return ans;
}
Poly Poly::transform(long *d)
{
	vector<long> t;
	vector<int> e;
	
	for(int i=0;i<ARRAY_MAX;i++){
		if(d[i]){
			t.push_back(d[i]);
			e.push_back(i);
		}
	}
	this->terms=this->capacity=t.size();
	this->t_array=new Term[this->terms];
	for(int i=0;i<this->terms;i++){
		this->t_array[i].coef=t[i];
		this->t_array[i].exp=e[i];
	}
	
	return *this;
}

Poly Poly::new_term(int e,__int128_t c)
{
	if(c==0)
		return *this;
	if(terms==capacity){
		capacity*=2;
		Term *t=new Term[capacity];
		for(int i=0;i<terms;i++){
			t[i]=t_array[i];
		}
		delete []t_array;
		t_array=t;
	}
	t_array[terms].exp=e;
	t_array[terms].coef=c;
	terms++;
	return *this;
}

Poly Poly::operator+(const Poly& b)
{
	Poly ans;
	int a_pos=0,b_pos=0;
	while(a_pos<terms && b_pos<b.terms){
		if(t_array[a_pos].exp==b.t_array[b_pos].exp && (t_array[a_pos].coef+b.t_array[b_pos].coef)){
			ans.new_term(t_array[a_pos].exp,(t_array[a_pos].coef+b.t_array[b_pos].coef));
			a_pos++;
			b_pos++;
		}
		else if(t_array[a_pos].exp<b.t_array[b_pos].exp){
			ans.new_term(t_array[a_pos].exp,t_array[a_pos].coef);
			a_pos++;
		}
		else{
			ans.new_term(b.t_array[b_pos].exp,b.t_array[b_pos].coef);
			b_pos++;
		}
	}
	for(;a_pos<terms;a_pos++){
		ans.new_term(t_array[a_pos].exp,t_array[a_pos].coef);
	}
	for(;b_pos<b.terms;b_pos++){
		ans.new_term(b.t_array[b_pos].exp,b.t_array[b_pos].coef);
	}
	return ans;
}

Poly Poly::operator-(const Poly& b)
{
	Poly ans;
	int a_pos=0,b_pos=0;
	while(a_pos<terms && b_pos<b.terms){
		if(t_array[a_pos].exp==b.t_array[b_pos].exp){
				ans.new_term(t_array[a_pos].exp,(t_array[a_pos].coef-b.t_array[b_pos].coef));
		}
			a_pos++;
			b_pos++;
		}
		else if(t_array[a_pos].exp<b.t_array[b_pos].exp){
			ans.new_term(t_array[a_pos].exp,t_array[a_pos].coef);
			a_pos++;
		}
		else{
			ans.new_term(b.t_array[b_pos].exp,-b.t_array[b_pos].coef);
			b_pos++;
		}
	}
	for(;a_pos<terms;a_pos++){
		ans.new_term(t_array[a_pos].exp,t_array[a_pos].coef);
	}
	for(;b_pos<b.terms;b_pos++){
		ans.new_term(b.t_array[b_pos].exp,-b.t_array[b_pos].coef);
	}
	return ans;
}

Poly Poly::operator*(const Poly& b)
{
	Poly ans;
	for(int i=0;i<b.terms;i++){
		Poly temp=*this;
		for(int j=0;j<terms;j++){
			temp.t_array[j].exp+=b.t_array[i].exp;
		}
		ans=ans+temp;
	}
	return ans;
}

Poly Poly::operator%(const Poly& b)
{
	Poly div;
	div.terms=terms;
	div.capacity=capacity;
	div.t_array=new Term[div.capacity];
	for(int i=0;i<div.terms;i++){
		div.t_array[i]=t_array[i];
	}
	int div_pos=div.terms-1;
	int mul_e;
	Poly temp;
	int cur_deg=div.t_array[div_pos].exp ,max_deg=b.t_array[b.terms-1].exp;
	
	while(div_pos>=0 && cur_deg>=max_deg){
		div.reduce();
		mul_e=div.t_array[div_pos].exp-b.t_array[b.terms-1].exp;
		
		__int128_t mul_div=b.t_array[b.terms-1].coef/gcd(div.t_array[div_pos].coef,b.t_array[b.terms-1].coef);
		__int128_t mul_b=div.t_array[div_pos].coef/gcd(div.t_array[div_pos].coef,b.t_array[b.terms-1].coef);
		
		temp.terms=b.terms;
		temp.capacity=b.capacity;
		temp.t_array=new Term[b.capacity];
		for(int i=0;i<temp.terms;i++){
			temp.t_array[i]=b.t_array[i];
		}
		
		for(int i=0;i<div.terms;i++){
			div.t_array[i].coef*=mul_div;
		}
		
		for(int i=0;i<temp.terms;i++){
			temp.t_array[i].exp+=mul_e;
			temp.t_array[i].coef*=mul_b;
		}
		
		div=div-temp;
	
		div.reduce();
		div_pos=div.terms-1;
		if(div.terms==0)
			break;
		cur_deg = div.t_array[div_pos].exp;
	}
	delete []temp.t_array;
	
	return div;
}
