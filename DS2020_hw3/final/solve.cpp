//
//  set.cpp
//  DS_hw3_Stack_and_queue 
//
/* ------------------------------- /
 * ------ BRUTE SOLUTION --------- /
 * -------------------------------*/
#include <algorithm>
#include "solve.h"

void solve::calculate(int target, int limit, int candidates_num, vector<int> candidates, vector< vector<int> > &solutions) {

  ans.clear(); ques_candidates.clear(); negative.clear(); Target.clear();
  ans_time = 0; neg_limit = limit; sum = 0;

  transform(target, limit, candidates_num, candidates);
  while(!Target.IsEmpty()){
    find(Target.num(), solutions);
    Target.Pop();
  }

//  Print_ans(solutions);

  return;
}

void solve::transform(int target, int limit, int candidates_num, vector<int> candidates){
  //push the candidates
  Stack<int> temp;
  for(int i = 0; i < candidates_num; i++){
    if(candidates[i] < 0)
      negative.Push(candidates[i]);
    else if(candidates[i] > 0)
      temp.Push(candidates[i]);
  }
  if(limit == 0)
    while(1){
      if(temp.Top() > target)
        temp.Pop();
      else
        break;
    }

  while(!temp.IsEmpty()){
    ques_candidates.Push(temp.Top());
    temp.Pop();
  }

  //calculate all the possible target
  Target.Push(target);
  if(!(negative.IsEmpty()) && limit != 0){
    switch(limit){
      case 1:
        //for one negative
        for(int i = negative.num(); i >= 0; i--)
          Target.Push(target - negative.term(i));
        break;
      case 2:
        //for one negative
        for(int i = negative.num(); i >= 0; i--)
          Target.Push(target - negative.term(i));
        //for two negative
        for(int i = negative.num(); i >= 0; i--)
          for(int j = i; j >= 0; j--)
            Target.Push(target - (negative.term(i) + negative.term(j)));
        break;
    }
  }
  return;
}

// recursive method to find the anwer
void solve::find(int t,vector< vector<int> > &s){
  //calculate the current sum
  
  /*
  int current = 0;
  for(int i = 0; i <= ans.num(); i++)
    current += ques_candidates.term(i) * ans.term(i);

  if(Target.term(t) == current){
  */
  
  if(Target.term(t) == sum){
    Push_ans(t, s); return;
  }

  if(ques_candidates.num() == ans.num())
    return;

  //for(int j = (Target.term(t) - current) / ques_candidates.term(ans.num() + 1); j >= 0; j--){
  for(int j = (Target.term(t) - sum) / ques_candidates.term(ans.num() + 1); j >= 0; j--){
    ans.Push(j);
    sum += ques_candidates.term(ans.num()) * j;
    find(t, s);
    sum -= ques_candidates.term(ans.num()) * j;
    ans.Pop();   
  }
}

void solve::Push_ans(int t, vector< vector<int> > & s){ 
  ans_time++;
  s.resize(ans_time);

  for(int i = 0; i <= ans.num(); i++)
    for(int j = 0; j < ans.term(i); j++)
      s[ans_time - 1].push_back(ques_candidates.term(i));
 
  if(t != 0){
    if(t <= negative.num()+1)
      s[ans_time -1].push_back(negative.term(negative.num() - (t - 1)));
    else{
      int i, j;
      for(i = negative.num(); i >= 0; i--)
        for(j = i; j >= 0; j--)
          if(Target.term(t) == (Target.term(0) - (negative.term(i) + negative.term(j))))
            break;
      s[ans_time -1].push_back(negative.term(i));
      s[ans_time -1].push_back(negative.term(j));
    }
  }
 
  return;
}

// Print ANS
void solve::Print_ans(vector< vector<int> > &s){
  cout << "\n-----------Start--------------\n";
  for(int i = 0; i < s.size(); i++){
    cout << i;
    for(int j = 0; j < s[i].size(); j++)
      cout << " " << s[i][j];
    cout << endl;
  }
  cout << "\n------------END---------------\n";
}


//---------------------------------------------------------------------------------------------//


/* -----------------------------------------------------------/
 * ---------------------- STACK PART -------------------------/
 * ----------------------------------------------------------*/

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
