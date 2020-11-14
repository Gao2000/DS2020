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

  find(solutions); 

  return;
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

void solve::find(vector< vector<int> > &s){
  //calculate the current sum
  int current = 0;
  for(int i = 0; i <= ans.num(); i++)
    current += ques_candidates.term(i) * ans.term(i);

  if(ques_candidates.num() == ans.num()){
    for(int i = 0; i <= Target.num(); i++)
      if(Target.term(i) == current){     // =
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
  ///*-------------------------------------------------------------*
  if(ans_time < 10){
    cout << endl;
    for(int i = 0; i <= ans.num(); i++)
      cout << ques_candidates.term(i) << " * " << ans.term(i) << endl;
    cout << endl;
  }
  ///--------------------------------------------------------------*/


  /*-------------------------------------------------------------*
    if(ans_time < 10){
    cout << "\n---Check---" << endl;
    cout << "Ans : " << ans_time << endl;
    for(int i = 0; i <= ans.num(); i++)
    cout << ques_candidates.term(i) << " * " << ans.term(i) << endl;
    cout << endl;
    }
  /--------------------------------------------------------------*/

  if(ans_time == 0){
    ans_time++;
    s.resize(ans_time);
    for(int i = 0; i <= ans.num(); i++)
      for(int j = 0; j < ans.term(i); j++)
        s[ans_time - 1].push_back(ques_candidates.term(i));
    Push_negative(t, s);
    return;
  }
  else{
    /*--------------------------------------------------------------/
     *--------------------DEALL WITH THIS SECTION!------------------/
     *-------------------------------------------------------------*/ 
    bool exist = false;
    for(int k = 0; k < s.size(); k++)
      for(int i = 0, temp = 0; (i <= ans.num()) && (temp < s[ans_time - 1].size()); i++)
        for(int j = 0; (j < ans.term(i)) && (temp < s[ans_time - 1].size()); j++){
          //cout << "check : " << ques_candidates.term(i) << " | " << s[ans_time - 1][temp] << endl;
          if(ques_candidates.term(i) == s[ans_time - 1][temp])
            return;
          temp++;
        }

    exist = true;
    if(exist){

      /*-------------------------------------------------------------*
      if(ans_time < 10){
        cout << endl;
        for(int i = 0; i <= ans.num(); i++)
          cout << ques_candidates.term(i) << " * " << ans.term(i) << endl;
        cout << endl;
      }
      /--------------------------------------------------------------*/

      ans_time++;
      s.resize(ans_time);
      for(int i = 0; i <= ans.num(); i++)
        for(int j = 0; j < ans.term(i); j++)
          s[ans_time - 1].push_back(ques_candidates.term(i));
      Push_negative(t, s);
      return;
    }
  }
}

void solve::Push_negative(int t, vector< vector<int> > &s){
  switch(neg_limit){
    case 0:
      break; 
    case 1:
      for(int i = negative.num(); i >= 0; i--)
        if(Target.term(t) == Target.term(0) - negative.term(i))
          s[ans_time - 1].push_back(negative.term(i));
      break;
    case 2:
      for(int i = negative.num(); i >= 0; i--)
        for(int j = i; j >= 0; j--)
          if(Target.term(t) == (Target.term(0) - (negative.term(i) + negative.term(j)))){
            s[ans_time - 1].push_back(negative.term(i));
            s[ans_time - 1].push_back(negative.term(j));
          }
      break;
  }
  ///*-----------------------------------------------------*/
  if(ans_time < 10){
    cout << endl;
    cout << "-------------------------------------Ans : " << ans_time << endl;
    for(int i = 0; i < s[ans_time - 1].size(); i++)
      cout << s[ans_time - 1][i] << endl;
    cout << endl;
  }
  //-------------------------------------------------------*/


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
