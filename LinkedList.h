#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // Add a new Node at the back
  void append(Node *node);

  // Remove a Node at an index
  void remove(int index);

  // Get a Node at in index
  Node *get(int index);

  // Utility methods
  bool isEmpty();
  int size();

private:
  // the beginning of the list
  Node *head;

  // how many nodes are there in the list?
  unsigned count;
};

#endif // LINKEDLIST_H
