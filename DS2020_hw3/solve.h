//
//  set.h
//  DS_hw3_Stack_and_queue 
//

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
    T& term(int) const;
};


class solve {
  private:
    Stack<int> ans, question;
  public:
    void calculate(int, int, int, vector<int>, vector< vector<int> > &);
    solve() {}
};

#endif
