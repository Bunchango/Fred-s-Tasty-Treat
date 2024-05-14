#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // Add a new Node at the back
  void append(Node *node);

  void removeNode(Node *node);
  void removeById(std::string id);

  // Get Node
  Node *getFirst();
  Node *getById(std::string id);

  // Utility methods
  bool isEmpty();
  int size();
  // Get the largest Id
  int getLargestId();

  // Sort by alphabetical order
  void sort();

private:
  // the beginning of the list
  Node *head;

  // how many nodes are there in the list?
  unsigned count;
};

#endif // LINKEDLIST_H
