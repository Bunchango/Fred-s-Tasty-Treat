#include "Node.h"

#include <sstream>
#include <string>

float Price::value() { return (float)dollars + (cents / 100.0f); }

int Price::valueAsDenom() { return this->value() * 100; }

FoodItem::FoodItem(std::string id, std::string name, std::string description,
                   Price price) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
    this->on_hand = DEFAULT_FOOD_STOCK_LEVEL;
}

bool FoodItem::isValidIdFormat(const std::string &id) {
    // Regular expression pattern to match the required format
    std::string pattern = "^F\\d{1," + std::to_string(IDLEN) + "}$";

    // Check if the string matches the pattern
    return std::regex_match(id, std::regex(pattern));
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