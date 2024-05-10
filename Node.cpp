#include "Node.h"

Node::Node() {
  // Create a new empty Node with data and next points to null
  this->data = nullptr;
  this->next = nullptr;
};
Node::~Node() {
  // Deallocate data in this node, but don't delete the next node
  if (this->data != nullptr) {
    delete this->data;
  }
};
