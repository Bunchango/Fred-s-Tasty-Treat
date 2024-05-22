#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <vector>

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
  if (!this->head) {
    this->head = node;
  } else {
    Node *current = this->head;
    while (current->next) {
      current = current->next;
    }
    current->next = node;
  }
  this->count++;
}

Node *LinkedList::getFirst() { return this->head; }

Node *LinkedList::getById(std::string id) {
  Node *current = this->head;
  Node *result = nullptr;
  while (current != nullptr) {
    // Use.compare() to compare std::string objects
    if (current->data->id.compare(id) == 0) { // Corrected line
      result = current;
    }
    current = current->next;
  }
  return result;
}

void LinkedList::remove(std::string id) {
  Node *current = this->head;
  Node *previous = nullptr;

  // Traverse the list to find the node that matches the ID
  while (current != nullptr && current->data->id != id) {
    previous = current;
    current = current->next;
  }

  // If the node is found
  if (current != nullptr) {
    // If the node found is the head of the LinkedList
    if (previous == nullptr) {
      // Then set the next Node as the new head
      head = current->next;
    } else {
      // If not, then redirect the pointer of the previous Node to skip a Node
      previous->next = current->next;
    }

    delete current;
    this->count--;
  }
}

bool LinkedList::isEmpty() {
  bool result = false;
  if (this->count == 0) {
    result = true;
  }
  return result;
}

int LinkedList::size() { return (int)this->count; }

int LinkedList::getNextId() {
  int largestId = 0;
  Node *current = this->head;

  // Traverse until the end of the LinkedList
  while (current != nullptr) {
    // Remove the first character F
    std::string numberStr = current->data->id.substr(1);
    // Convert the remaining to integer
    int number = std::stoi(numberStr);

    if (number > largestId) {
      largestId = number;
    }

    current = current->next;
  }

  return largestId + 1;
}

std::vector<float> LinkedList::getPrices() {
  std::vector<float> prices = {};
  Node *current = this->head;

  while (current != nullptr) {
    prices.push_back(current->data->price.value());
    current = current->next;
  }

  return prices;
}

void LinkedList::sortByAlpha() {
  if (this->head == nullptr || this->head->next == nullptr)
    return; // No need to sort if list is empty or has only one element

  bool swapped;
  Node *ptr1 = nullptr;
  Node *last = nullptr;

  do {
    swapped = false;
    ptr1 = head;

    while (ptr1->next != last) {
      if (ptr1->data->name > ptr1->next->data->name) {
        // Swap the data of ptr1 and ptr1->next
        std::swap(ptr1->data, ptr1->next->data);
        swapped = true;
      }
      ptr1 = ptr1->next;
    }
    last = ptr1;
  } while (swapped);
}
