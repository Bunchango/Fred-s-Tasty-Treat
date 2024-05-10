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
    this->head = nullptr;
  }
}

void LinkedList::append(Node *node) {
  Node *currentNode = this->head;
  while (currentNode != nullptr) {
    // If currentNode is not the last Node, then get the next Node
    currentNode = currentNode->next;
  }

  // By now currentNode should be the last Node, so we add the next Node behind
  // it And we don't need to deallocate since the last node is a nullptr
  currentNode->next = node;

  // Update count
  this->count++;
}

void LinkedList::remove(int index) {
  // Get the previous node
  Node *previousNode = this->get(index - 1);
  // Get the Node after the next Node and delete the next Node
  Node *nextNode = previousNode->next;
  Node *newNextNode = nextNode->next;

  delete nextNode; // Delete the next Node
  previousNode->next = newNextNode;
}

Node *LinkedList::get(int index) {
  int current = 0;
  Node *currentNode = this->head;

  // Get the node at the given index
  // If the index is out of bound, get the last item of the LinkedList
  while (currentNode != nullptr && current < index &&
         current < (int)this->count) {
    current++;
    currentNode = this->head->next;
  }

  // By now, the nextNode should either be the last Node, or the Node at desired
  // index
  return currentNode;
}

bool LinkedList::isEmpty() {
  bool result = false;
  if (this->count == 0) {
    result = true;
  }
  return result;
}

int LinkedList::size() { return (int)this->count; }
