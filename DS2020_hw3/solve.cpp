//
//  set.cpp
//  DS_hw3_Stack_and_queue 
//

#include <algorithm>
#include "solve.h"

void solve::calculate(int target, int limit, int candidates_num, vector<int> candidates, vector< vector<int> > &solutions) {
  transform(target, limit, candidates_num, candidates);

  /*--------------------------------------------------*
    cout << "Ques : ";
    for(int i = 0; i <= ques_candidates.num(); i++)
    cout << ques_candidates.term(i) << " ";
    cout << endl;
    cout << "Target : ";
    for(int i = 0; i <= Target.num(); i++)
    cout << Target.term(i) << " ";
    cout << endl;
   *--------------------------------------------------*/

  find(); 

  ans.clear(); ques_candidates.clear(); negative.clear(); Target.clear();
  ans_time = 0;
}

void solve::transform(int target, int limit, int candidates_num, vector<int> candidates){
  Target.Push(target);

  for(int i = 0; i < candidates_num; i++){
    if(candidates[i] < 0){
      negative.Push(candidates[i]);
      //cout << candidates[i] << endl;
    }else if(candidates[i] > 0){
      ques_candidates.Push(candidates[i]);
      //cout << candidates[i] << endl;
    }
  }
  /*--------------------------------------------------*
    cout << "Ques : ";
    for(int i = 0; i <= ques_candidates.num(); i++)
    cout << ques_candidates.term(i) << " ";
    cout << endl;
   *--------------------------------------------------*/

  if(!(negative.IsEmpty()) && limit != 0){
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

bool solve::find(){
  bool has_find = false;
  //calculate the current sum
  int current = 0;
  for(int i = 0; i <= ans.num(); i++)
    current += ques_candidates.term(i) * ans.term(i);

  if(ques_candidates.num() == ans.num()){
    for(int i = 0; i <= Target.num(); i++)
      if(Target.term(i) == current){     // =
        has_find = true; 
        Push_ans(); 
        continue; 
      }
    return has_find;
  }

  for(int i = 0; i <= Target.num(); i++){
    if(Target.term(i) < current)            // <
      continue;
    else if(Target.term(i) == current){     // =
      has_find = true;
      Push_ans(); 
      continue; 
    }
    else{                                   // >
      for(int j = (Target.term(i) - current) / ques_candidates.term(ans.num() + 1); j >= 0; j--){
        ans.Push(j);
        if(find()){
          ans.Pop();
          break;
        }
        ans.Pop();
      }
    }
  }
}

void solve::Push_ans(){
  if(ans_time < 10){
    ans_time++;
    cout << endl;
    cout << "Ans : " <<ans_time << endl;
    for(int i = 0; i <= ans.num(); i++)
      cout << i << ":" << ques_candidates.term(i) << "*" << ans.term(i) << endl;
    cout << endl;
  }
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
  capacity = 10;
}
