#include "LinkedList.h"

LinkedList::LinkedList() {
  this->head = nullptr;
  this->count = 0;
}

LinkedList::~LinkedList() {
  // Delete all nodes to prevent memory leaks
  while (head != nullptr) {
    Node *temp = this->head;
    this->head = this->head->next;
    delete temp;
  }
}

void LinkedList::append(Node *node) {
  if (!head) {
    head = node;
  } else {
    Node *currentNode = head;
    while (currentNode->next) {
      currentNode = currentNode->next;
    }
    currentNode->next = node;
  }
  this->count++;
}

Node *LinkedList::getFirst() { return this->head; }

bool LinkedList::isEmpty() {
  bool result = false;
  if (this->count == 0) {
    result = true;
  }
  return result;
}

int LinkedList::size() { return (int)this->count; }
