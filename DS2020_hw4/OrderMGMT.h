#ifndef ORDERMGMT_H
#define ORDERMGMT_H

#include <list>

using namespace std;

// Data structure consisting of Order ID and date.
struct Node {
  unsigned id;
  unsigned date;
  unsigned leftSize;
  Node *left, *right;
  //-------- New --------//
  Node *parent;
};


// Order Management System consolidating key operational processes.
class OrderMGMT {
  private:
    Node *root;

  public:
    OrderMGMT():root(0){};
    void addOrder(unsigned date, unsigned id);
    void deleteOrders(unsigned start, unsigned end);
    list<unsigned> searchByDate(unsigned start, unsigned end);
    list<unsigned> searchByDateRank(unsigned a_th, unsigned b_th);
    //-------- New --------//
    void deleteTree(unsigned date);
    Node *Search(unsigned date);
    Node *Successor(Node *current);
    Node *leftMost(Node *current);
    void inorderPrint();
};

#endif

