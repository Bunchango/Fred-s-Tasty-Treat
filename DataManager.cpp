#include "DataManager.h"
#include "Coin.h"
#include "Helper.h"
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

DataManager::DataManager(std::string mealFileName, std::string moneyFileName) {
  // Create an empty LinkedList and balance
  this->meals = new LinkedList();
  this->balance = Balance();

  std::ifstream mealFile(mealFileName);
  std::ifstream moneyFile(moneyFileName);

  // Read the meal file
  std::string line;
  while (std::getline(mealFile, line)) {
    // Process each line: Create a new FoodItem, assign it to a Node, then add
    // that Node to LinkedList
    std::vector<std::string> tokens = {};
    std::vector<std::string> prices = {};
    Helper::splitString(line, tokens, "|");

    if (tokens.size() == 4 && Helper::isNumber(tokens[3]) &&
        tokens[1].size() <= NAMELEN && tokens[2].size() <= DESCLEN &&
        FoodItem::isValidIdFormat(tokens[0]) &&
        Helper::isValidFloat(tokens[3]) &&
        Price::isValidPrice(std::stof(tokens[3]))) {
      // Slit the price into its integer and fractional part to create Price
      // object
      Helper::splitString(Helper::floatToString(std::stof(tokens[3]), 2),
                          prices, ".");
      Price price = Price();
      price.dollars = std::stoi(prices[0]);
      price.cents = std::stoi(prices[1]);

      // Create FoodItem object
      FoodItem *item = new FoodItem(tokens[0], tokens[1], tokens[2], price);

      // Create node
      Node *node = new Node();
      node->data = item;

      this->meals->append(node);
    }
  }

  while (std::getline(moneyFile, line)) {
    // Process each line: Split by "." and create Coin objects
    std::vector<std::string> tokens = {};
    Helper::splitString(line, tokens, DELIM);

    if (tokens.size() == 2 && Helper::isNumber(tokens[0]) &&
        Helper::isNumber(tokens[1]) && Coin::isDenomination(tokens[0]) &&
        Helper::isValidInteger(tokens[1])) {
      Coin coin = Coin();
      coin.denom = Coin::intToDenomination(std::stoi(tokens[0]));
      coin.count = std::stoi(tokens[1]);
      // Insert coin to Balance
      this->balance.insert(coin);
    }
  }

  // Sort the LinkedList
  this->meals->sortByAlpha();

  // Close the files
  mealFile.close();
  moneyFile.close();
}

DataManager::~DataManager() { delete this->meals; }

void DataManager::save() {}
