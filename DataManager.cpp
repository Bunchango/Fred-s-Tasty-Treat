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

    Helper::splitString(line, tokens, "|");

    if (tokens.size() == 4 && Helper::isNumber(tokens[3]) &&
        tokens[0].size() <= IDLEN && tokens[1].size() <= NAMELEN &&
        tokens[2].size() <= DESCLEN) {
      // Slit the price into its integer and fractional part to create Price
      // object
      std::vector<int> splitPrice = Helper::splitFloat(std::stof(tokens[3]));
      Price price = Price();
      price.dollars = splitPrice[0];
      price.cents = splitPrice[1];

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
        Helper::isNumber(tokens[1]) &&
        Coin::isDenomination(std::stoi(tokens[0]))) {
      Coin coin = Coin();
      coin.denom = Coin::intToDenomination(std::stoi(tokens[0]));
      coin.count = std::stoi(tokens[1]);
      // Insert coin to Balance
      this->balance.insert(coin);
    }
  }

  // Test
  displayMeals();
  std::cout << "\n";
  displayBalance();

  // Close the files
  mealFile.close();
  moneyFile.close();
}

DataManager::~DataManager() { delete this->meals; }

// TODO: Reimplement display functions

void DataManager::displayMeals() {
  Node *currentMeal = this->meals->getFirst();

  // Display first row
  std::cout << "ID";
  for (int i = 0; i < IDLEN - 2;
       i++) { // Accounting for the length of string ID
    std::cout << EMPTY_SPACE;
  }

  std::cout << SEPARATOR << "Name";
  for (int i = 0; i < NAMELEN - 4; i++) {
    std::cout << EMPTY_SPACE;
  }
  std::cout << SEPARATOR << "Length";
  for (int i = 0; i < PRICELEN - 6; i++) {
    std::cout << EMPTY_SPACE;
  }

  std::cout << "\n";
  // Display separator line
  for (int i = 0; i < IDLEN + NAMELEN + PRICELEN + SEPARATOR_NUM; i++) {
    std::cout << LINE;
  }
  std::cout << "\n";

  while (currentMeal != nullptr) {
    std::cout << currentMeal->data->id << SEPARATOR << currentMeal->data->name;
    for (int i = 0; i < NAMELEN - currentMeal->data->name.size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << MONEY_SYMBOL;

    for (int i = 0;
         i < PRICELEN - EXCESS_LINE -
                 Helper::floatToString(currentMeal->data->price.value()).size();
         i++) {
      std::cout << EMPTY_SPACE;
    }

    std::cout << Helper::floatToString(currentMeal->data->price.value())
              << "\n";
    currentMeal = currentMeal->next;
  }
}

void DataManager::displayBalance() {
  // Display first row
  std::cout << "Denom  " << SEPARATOR << " Quantity " << SEPARATOR << " Value ";

  std::cout << "\n";
  // Display separator line
  for (int i = 0;
       i < DENOM_LENGTH + QUANTITY_LENGTH + VALUE_LENGTH + SEPARATOR_NUM * 2;
       i++) {
    std::cout << LINE;
  }
  std::cout << "\n";

  for (Coin coin : this->balance.balance) {
    std::cout << coin.denom;
    for (int i = 0; i < DENOM_LENGTH - std::to_string(coin.denom).size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << EMPTY_SPACE << coin.count;

    for (int i = 0; i < QUANTITY_LENGTH - std::to_string(coin.count).size();
         i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << MONEY_SYMBOL;

    for (int i = 0;
         i < VALUE_LENGTH - Helper::floatToString(coin.getTotal()).size();
         i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << Helper::floatToString(coin.getTotal()) << "\n";
  }
}

void DataManager::save() {}
