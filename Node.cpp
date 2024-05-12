#include "Node.h"

FoodItem::FoodItem(std::string id, std::string name, std::string description,
                   Price price) {
  this->id = id;
  this->name = name;
  this->description = description;
  this->price = price;
  this->on_hand = DEFAULT_COIN_COUNT;
}

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
