#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // more functions to be added perhaps...

private:
  // the beginning of the list
  Node *head;

  // how many nodes are there in the list?
  unsigned count;
};

#endif // LINKEDLIST_H
