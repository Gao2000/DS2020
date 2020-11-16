//
//  set.h
//  DS_hw3_Stack_and_queue 
//
/* ------------------------------- /
 * ------ BRUTE SOLUTION --------- /
 * -------------------------------*/
#ifndef __DS_hw3_solve__
#define __DS_hw3_solve__

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>

using namespace std;

template<class T>
class Stack{
  friend class solve;
  private:
    T * stack;
    int top;
    int capacity;
  public:
    Stack(int stackcapacity = 10);
    ~Stack();
    T& Top() const;
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& term(int) const; // return stack[int]
    int num() const; // return the total term num
    void clear();
};


class solve {
  private:
    Stack<int> ans, ques_candidates, negative, Target;
    int ans_time;
    int neg_limit;
  public:
    void calculate(int, int, int, vector<int>, vector< vector<int> > &);
    void transform(int, int, int, vector<int>);
    void find(int, vector< vector<int> > &);
    void Push_ans(int, vector< vector<int> > &);
    void Print_ans(vector< vector<int> > &);
    solve() {}
};

#endif
