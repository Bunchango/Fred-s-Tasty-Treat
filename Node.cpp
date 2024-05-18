#include "Node.h"
#include "Helper.h"
#include <regex>
#include <string>
#include <vector>

float Price::value() { return (float)dollars + (cents / 100.0f); }

int Price::valueAsDenom() { return this->value() * 100; }

bool Price::isValidPrice(std::string price) {
  // A valid price is a price that is divisable by 5 after being multipled by
  // 100 and smaller than 100
  std::vector<std::string> tokens = {};
  Helper::splitString(price, tokens, ".");
  bool result = false;

  std::regex pattern(".*[05]$");
  if (tokens.size() == 2 && Helper::isNumber(price) && tokens[1].size() == 2 &&
      std::regex_match(tokens[1], pattern) && Helper::isValidFloat(price) &&
      std::stof(price) <= 100) {
    result = true;
  }
  return result;
}

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

std::string FoodItem::constructID(int id) {
  // This function assumes id is a valid id, that is id has less than 5
  // characters
  std::string result = "F";
  std::string idAsStr = std::to_string(id);
  for (int i = 0; i < 4 - idAsStr.size(); i++) {
    result.append("0");
  }
  result.append(idAsStr);
  return result;
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