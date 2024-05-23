#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <vector>

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // Add a new Node at the back
  void append(Node *node);

  void remove(std::string id);

  // Get Node
  Node *getFirst();
  Node *getById(std::string id);

  // Utility methods
  bool isEmpty();
  int size();
  // Get the next Id of all the Nodes in the LinkedList
  int getNextId();

  // Get all prices
  std::vector<float> getPrices();

  // Sort the LinkedList by alphabetical order
  void sortByAlpha();

private:
  // the beginning of the list
  Node *head;

  // how many nodes are there in the list?
  unsigned count;
};

#endif // LINKEDLIST_H
