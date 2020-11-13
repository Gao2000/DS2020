//
//  set.cpp
//  DS_hw3_Stack_and_queue 
//

#include <algorithm>
#include "solve.h"

void solve::calculate(int target, int limit, int candidates_num, vector<int> candidates, vector< vector<int> > &solutions) {
    
    
    
    
}

//Stack part
template<class T>
Stack<T>::Stack(int stackcapacity): capacity(stackcapacity){
  if(capacity < 1) throw "Stack must be > 0";
  top = -1;
  stack = new int[capacity];
}

template<class T>
inline bool Stack<T>::IsEmpty() const { return top == -1;}

template<class T>
inline T& Stack<T>::Top() const {
  if(IsEmpty()) throw "Stack is empty!!";
  return stack[top];
}

template<class T>
void ChangeSize1D(T * &arr,const int& size,const int& ToSize){
      T* tmp = new T[size];
      tmp = arr;
      arr = new T[ToSize];
      for(int i=0; i< size; ++i){
      arr[i] = tmp[i];
      }
      delete[] tmp;
}

template<class T>
void Stack<T>::Push(const  T& x) {
  if(top == capacity - 1){
    ChangeSize1D(stack, capacity, capacity * 2);
    capacity *= 2;
  }
  stack[++top] = x;
}

template<class T>
void Stack<T>::Pop(){
  if(IsEmpty()) throw "Stack is empty!! Cannot delete";
  stack[top--].~T();
}

template<class T>
T& Stack<T>::term(int n) const {
  if(IsEmpty()) throw "Stack is empty!!";
  if(n < top)
    return stack[n];
}
