#include "LinkedList.h"

LinkedList::LinkedList() {
  this->head = nullptr;
  this->count = 0;
}

LinkedList::~LinkedList() {
  // Delete all nodes to prevent memory leaks
  Node *current = this->head;
  while (current != nullptr) {
    Node *next = current->next;
    // Delete food item stored in the Node
    delete next->data;
    // Delete the node itself
    delete next;
    // Set the head to nullptr
    current = next;
  }
}
