//
//  set.cpp
//  DS_hw3_Stack_and_queue 
//

#include <algorithm>
#include "solve.h"

void solve::calculate(int target, int limit, int candidates_num, vector<int> candidates, vector< vector<int> > &solutions) {
  transform(target, limit, candidates_num, candidates);

  /*--------------------------------------------------*/
  cout << "Ques : ";
  for(int i = 0; i <= ques_candidates.num(); i++)
    cout << ques_candidates.term(i) << " ";
  cout << endl;
  cout << "Target : ";
  for(int i = 0; i <= Target.num(); i++)
    cout << Target.term(i) << " ";
  cout << endl;
  /*--------------------------------------------------*/

  ans.clear(); ques_candidates.clear(); negative.clear(); Target.clear();
}

void solve::transform(int target, int limit, int candidates_num, vector<int> candidates){
  Target.Push(target);
  
  for(int i = 0; i < candidates_num; i++){
    if(candidates[i] < 0){
      negative.Push(candidates[i]);
      cout << candidates[i] << endl;
    }else if(candidates[i] > 0){
      ques_candidates.Push(candidates[i]);
      cout << candidates[i] << endl;
    }
  }
  /*--------------------------------------------------*
  cout << "Ques : ";
  for(int i = 0; i <= ques_candidates.num(); i++)
    cout << ques_candidates.term(i) << " ";
  cout << endl;
  *--------------------------------------------------*/
  
  if(!(negative.IsEmpty()) && limit != 0){
    
    cout << "Neg : ";
    for(int i = 0; i <= negative.num(); i++)
      cout << negative.term(i) << " ";
    cout << endl;
    
    switch(limit){
      case 1:
        for(int i = negative.num(); i >= 0; i--)
          Target.Push(target - negative.term(i));
        break;
      case 2:
        for(int i = negative.num(); i >= 0; i--)
          for(int j = i; j >= 0; j--)
            Target.Push(target - (negative.term(i) + negative.term(j)));
        break;
    }
  }
  return;
}

//Stack part
template<class T>
Stack<T>::Stack(int stackcapacity): capacity(stackcapacity){
  if(capacity < 1) cout << "Stack must be > 0" << endl;
  top = -1;
  stack = new T[capacity];
}

template<class T>
Stack<T>::~Stack(){
  delete stack;
}

template<class T>
inline bool Stack<T>::IsEmpty() const { return top == -1;}

template<class T>
inline T& Stack<T>::Top() const {
  if(IsEmpty()) cout << "Stack is empty!!" << endl;
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
  if(IsEmpty()) cout << "Stack is empty!! Cannot delete" << endl;
  stack[top--].~T();
}

template<class T>
T& Stack<T>::term(int n) const {
  if(IsEmpty()) cout << "Stack is empty!!" << endl;
  if(n <= top)
    return stack[n];
}

template<class T>
int Stack<T>::num() const{
  return top;
}

template<class T>
void Stack<T>::clear(){
  delete stack;
  stack = new T[10];
  top = -1;
  capacity = 0;
}
