//
//  set.cpp
//  DS_hw3_Stack_and_queue 
//

#include <algorithm>
#include "solve.h"

void solve::calculate(int target, int limit, int candidates_num, vector<int> candidates, vector< vector<int> > &solutions) {

  ans.clear(); ques_candidates.clear(); negative.clear(); Target.clear();
  ans_time = 0; neg_limit = limit;

  transform(target, limit, candidates_num, candidates);

  find(solutions); 

  //Print_ans(solutions);

  return;
}

void solve::transform(int target, int limit, int candidates_num, vector<int> candidates){
  Target.Push(target);

  for(int i = 0; i < candidates_num; i++){
    if(candidates[i] < 0)
      negative.Push(candidates[i]);
    else if(candidates[i] > 0)
      ques_candidates.Push(candidates[i]);
  }

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

// recursive method to find the anwer
void solve::find(vector< vector<int> > &s){
  //calculate the current sum
  int current = 0;
  for(int i = 0; i <= ans.num(); i++)
    current += ques_candidates.term(i) * ans.term(i);

  if(ques_candidates.num() == ans.num()){
    for(int i = 0; i <= Target.num(); i++)
      if(Target.term(i) == current){        // =
        Push_ans(i, s);
        return;
      }
    return;
  }

  for(int i = 0; i <= Target.num(); i++){
    if(Target.term(i) < current)            // <
      continue;
    else{                                   // >
      for(int j = (Target.term(i) - current) / ques_candidates.term(ans.num() + 1); j >= 0; j--){
        ans.Push(j);
        find(s);
        ans.Pop();
      }
    }
  }
}

void solve::Push_ans(int t, vector< vector<int> > & s){
  vector <int> temp;
  for(int i = 0; i <= ans.num(); i++)
    for(int j = 0; j < ans.term(i); j++)
      temp.push_back(ques_candidates.term(i));
  switch(neg_limit){
    case 0:
      break; 
    case 1:
      if(t == 0) break;
      for(int i = negative.num(); i >= 0; i--)
        if(Target.term(t) == Target.term(0) - negative.term(i))
          temp.push_back(negative.term(i));
      break;
    case 2:
      if(t == 0) break;
      for(int i = negative.num(); i >= 0; i--)
        for(int j = i; j >= 0; j--)
          if(Target.term(t) == (Target.term(0) - (negative.term(i) + negative.term(j)))){
            temp.push_back(negative.term(i));
            temp.push_back(negative.term(j));
          }
      break;
  }

  if(ans_time == 0){
    ans_time++;
    s.resize(ans_time);
    s[ans_time - 1].insert(s[ans_time - 1].end(), temp.begin(), temp.end());
    return;
  }
  else{
    bool exist = true;
    for(int i = 0; i < s.size(); i++)
      if(temp == s[i])
        exist = false;
    
    if(exist){

      ans_time++;
      s.resize(ans_time);
      s[ans_time - 1].insert(s[ans_time - 1].end(), temp.begin(), temp.end());
      return;
    }
  }
}

// Print ANS
void solve::Print_ans(vector< vector<int> > &s){
  for(int i = 0; i < s.size(); i++){
    cout << i;
    for(int j = 0; j < s[i].size(); j++)
      cout << " " << s[i][j];
    cout << endl;
  }
  cout << "\n------------END---------------\n";
}

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
