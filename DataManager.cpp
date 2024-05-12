#include "DataManager.h"
#include "Coin.h"
#include "Helper.h"
#include <fstream>
#include <string>

DataManager::DataManager(std::string mealFileName, std::string moneyFileName) {
  std::ifstream mealFile(mealFileName);
  std::ifstream moneyFile(moneyFileName);

  // Read the meal file
  std::string line;
  while (std::getline(mealFile, line)) {
    // Process each line: Create a new FoodItem, assign it to a Node, then add
    // that Node to LinkedList
    std::vector<std::string> formatted = {};
    std::vector<std::string> price_string = {};

    Helper::splitString(line, formatted, "|");
    Helper::splitString(formatted[3], price_string, ".");

    // Create price
    Price price;
    price.dollars = std::stof(price_string[0]);
    price.cents = std::stof(price_string[1]);

    // Create FoodItem
    FoodItem *item =
        new FoodItem(formatted[0], formatted[1], formatted[2], price);

    // Create Node
    Node *node = new Node();
    node->data = item;

    // Add to LinkedList
    this->meals->append(node);
  }

  while (std::getline(moneyFile, line)) {
    std::vector<std::string> formatted = {};
    Helper::splitString(line, formatted, DELIM);
    // Create Coin objects
    Coin coin = Coin();
    coin.denom = Coin::intToDenomination(std::stoi(formatted[0]));
    coin.count = std::stoi(formatted[1]);
    // Insert coins into Register
  }

  // Close the files
  mealFile.close();
  moneyFile.close();
}

DataManager::~DataManager() { delete this->meals; }

void DataManager::displayMeals() {}

void DataManager::displayBalance() {}
