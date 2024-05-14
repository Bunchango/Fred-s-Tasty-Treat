#include "Node.h"

#include <string>

float Price::value() { return (float)dollars + (cents / 100.0f); }

FoodItem::FoodItem(std::string id, std::string name, std::string description,
                   Price price) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
    this->on_hand = DEFAULT_FOOD_STOCK_LEVEL;
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
