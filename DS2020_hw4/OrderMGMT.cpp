#include "OrderMGMT.h"
#include <iostream>
using namespace std;


// Function to insert a new order.
// date: Date of a order.
// id: Order ID.
void OrderMGMT::addOrder(unsigned date, unsigned id){
  if(Search(date) != NULL)
    return;

  Node *parent = 0; // parent Node
  Node *sentry = 0; // sentry Node(哨兵)
  
  //initial insertNode
  Node *insertNode = new Node;
  insertNode->id = id; insertNode->date = date; insertNode->leftSize = 0;
  insertNode->left = 0; insertNode->right = 0; insertNode->parent = 0;

  sentry = root;
  while(sentry != NULL){
    parent = sentry;    //let parent be the current sentry position
    if(insertNode->date < sentry->date)
      sentry = sentry->left;
    else
      sentry = sentry->right;
  }

  insertNode->parent = parent;

  //BST is empty
  if(parent == NULL)
    this->root = insertNode;
  //small than parent
  else if(insertNode->date < parent->date)
    parent->left = insertNode;
  //bigger
  else
    parent->right = insertNode;
  
  /* ==================== DEBUG ======================
  cout << "insertNode: " << date << ',' << id << endl;
  cout << "\n------ after insert ------" << endl;
  inorderPrint();
  cout << "-------end of addNode--------\n" << endl;
  // ================================================= */

}


// Function to delete orders from a given range.
// start: Begin date.
// end: End date.
void OrderMGMT::deleteOrders(unsigned start, unsigned end){
  for(int i = start; i <= end; i++)
    deleteTree(i);
  /* ==================== DEBUG ====================== 
  cout << "\ndeletetNode: " << start << ',' << end << endl;
  cout << "\n------- delete Node -------" << endl;
  inorderPrint();
  cout << "--------end of delete---------\n" << endl;
  // ================================================= */
}


// Function to return a STL list of order IDs from a given range of dates.
// start: Begin date.
// end: End date.
list<unsigned> OrderMGMT::searchByDate(unsigned start, unsigned end){
  list<unsigned> ans;
  Node *current = new Node;

  current = leftMost(root);
  while(current != NULL){
    if(current->date >= start && current->date <= end)
      ans.push_back(current->id);
    current = Successor(current);
  }

  /* ==================== DEBUG ====================== 
  cout << "\n------ans by date-------" << endl;
  cout << "\nByDate: " << start << ',' << end << endl;
  for(list<unsigned>::iterator j = ans.begin(); j != ans.end(); j++)
    cout << *j << " ";
  cout << "\n-----end of by date-----\n" << endl;
  // ================================================= */
  
  return ans;
}


// Function to return a STL list of order IDs starting from the a_th rank of date to the b_th rank of date.
// a_th: Begin rank.
// b_th: End rank.
list<unsigned> OrderMGMT::searchByDateRank(unsigned a_th, unsigned b_th){
  list<unsigned> ans;
  Node *current = new Node;

  current = leftMost(root);
  while(current != NULL){
    ans.push_back(current->id);
    current = Successor(current);
  }

  for(int i = 1; i < a_th; i++)
    ans.pop_front();

  while(ans.size() != (b_th - a_th + 1))
    ans.pop_back();

  /* ==================== DEBUG ====================== 
  cout << "\n------ans by rank-------" << endl;
  cout << "\nByRank: " << a_th << ',' << b_th << endl;
  for(list<unsigned>::iterator j = ans.begin(); j != ans.end(); j++)
    cout << *j << " ";
  cout << "\n-----end of by rank-----\n" << endl;
  // ================================================= */

  return ans;
}


//Function to delete Node from BST
//date is the key
void OrderMGMT::deleteTree(unsigned date){
  Node *deleteNode = Search(date);
  //NOT Found
  if(deleteNode == NULL)
    return;

  Node *y = 0;  //the real Node need to be delete and release register
  Node *x = 0;  //the child of Node y

  if(deleteNode->left == NULL || deleteNode->right == NULL)
    y = deleteNode;
  else
    y = Successor(deleteNode); // let y be deleteNode's Successor
                               // after this step, y will be case 1 or 2(no two child

  if(y->left != NULL)
    x = y->left;
  else
    x = y->right;

  if(x != NULL)
    x->parent = y->parent;

  if(y->parent == NULL) //y's root
    this->root = x;
  else if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  if(y != deleteNode){
    deleteNode->date = y->date;
    deleteNode->id = y->id;
  }

  delete y;
  y = 0;
}


//Function to Search the Node by date
Node *OrderMGMT::Search(unsigned date){
  Node *current = root;
  if(current == NULL)
    return current;
  // Two condtion to break the loop
  // 1. Not found
  // 2. Found
  while(current != NULL && date != current->date){
    if(date < current->date)
      current = current->left;
    else
      current = current->right;
  }
  
  return current;
}


//Function to find the Successor
Node *OrderMGMT::Successor(Node *current){
  if(current->right != NULL)
    return leftMost(current->right);

  Node *newNode = current->parent;

  while(newNode != NULL && current == newNode->right){
    current = newNode;
    newNode = newNode->parent;
  }
  
  return newNode;
}

Node *OrderMGMT::leftMost(Node *current){
  while(current->left != NULL)
    current = current->left;
  return current;
}

void OrderMGMT::inorderPrint(){
  if(root == NULL)
    return;
  Node *current = new Node;
  current = leftMost(root);
  cout << "inorderPrint--Start\n";
  while(current){
    cout << current->date << "," << current->id << endl;
    current = Successor(current);
  }
  cout << "inorderPrint--End\n" << endl;
}

