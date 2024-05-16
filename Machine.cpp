#include "Machine.h"
#include "DataManager.h"
#include "Helper.h"
#include "iostream"
#include <string>
Machine::Machine(std::string mealFileName, std::string moneyFileName) {
  DataManager *data = new DataManager(mealFileName, moneyFileName);
  this->data = data;
}

Machine::~Machine() {
  // Deallocate the LinkedList
  delete this->data;
}

void Machine::start() {
  bool run = true;

  while (run) {
    std::cout << "Main Menu:\n"
                "\t1. Display Meal Options\n"
                "\t2. Purchase Meal\n"
                "\t3. Save and Exit\n"
                "Administrator-Only Menu:\n"
                "\t4. Add Food\n"
                "\t5. Remove Food\n"
                "\t6. Display Balance\n"
                "\t7. Abort Program\n"
                "Select your option (1-7) : ";
    std::string input = Helper::readInput();
    std::cout << "\n";

    if (input == "1") {
      this->displayMeals();
    } else if (input == "2") {
          std::cout << "Purchase Meal\n"
                      "-------------\n";
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string input = Helper::readInput();
        purchaseMeal(input);
    } else if (input == "3") {
      std::cout << "Save and exit";
    } else if (input == "4") {
      std::cout << "Add food";
    } else if (input == "5") {
      std::cout << "Remove food";
    } else if (input == "6") {
      this->displayBalance();
    } else if (input == "7") {
      std::cout << "Abort";
      run = false;
    } else {
      Helper::printInvalidInput();
    }
    std::cout << "\n";
  }
}

void Machine::purchaseMeal(std::string mealID) {
    if (mealID == "F0001") {
        std::cout << "You have selected ";
        std::cout << this->data->meals->getById("F0001")->data->name;
    } else {
        Helper::printInvalidInput();
    }
}

void Machine::displayMeals() {
  Node *currentMeal = this->data->meals->getFirst();

  // Display first row
  std::cout << "ID";
  for (int i = 0; i < IDLEN - 2;
       i++) { // Accounting for the length of string ID
    std::cout << EMPTY_SPACE;
  }

  // Get the maximum size of PRICELEN
  int longestInteger = Helper::getLongestIntegerPart(this->data->meals->getPrices());
  int pricelen = longestInteger + 3;

  std::cout << SEPARATOR << "Name";
  for (int i = 0; i < NAMELEN - 4; i++) {
    std::cout << EMPTY_SPACE;
  }
  std::cout << SEPARATOR << "Length";
  for (int i = 0; i < pricelen - 6; i++) {
    std::cout << EMPTY_SPACE;
  }

  std::cout << "\n";
  // Display separator line
  for (int i = 0; i < IDLEN + NAMELEN + pricelen + 3 + SEPARATOR_NUM; i++) {
    std::cout << LINE;
  }
  std::cout << "\n";

  while (currentMeal != nullptr) {
    std::cout << currentMeal->data->id << SEPARATOR << currentMeal->data->name;
    for (int i = 0; i < NAMELEN - currentMeal->data->name.size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << MONEY_SYMBOL;

    std::cout << Helper::formatFloatToString(currentMeal->data->price.value(),
                                             longestInteger)
              << "\n";
    currentMeal = currentMeal->next;
  }
}

void Machine::displayBalance() {
// Get maximum quantity and value length
  int quantlen = Helper::floatToString(this->data->balance.getMaxValue(), 0).size();
  int valuelen = Helper::floatToString(this->data->balance.getMaxValue(), 2).size();

  if (quantlen < DEFAULT_QUANTITY_LENGTH) {
    quantlen = DEFAULT_QUANTITY_LENGTH;
  }

  if (valuelen < DEFAULT_VALUE_LENGTH) {
    valuelen = DEFAULT_VALUE_LENGTH;
  }

  // Display the first row
  std::cout << "Denom  " << SEPARATOR;

  std::cout << EMPTY_SPACE << "Quantity";
  for (int i = 0; i < quantlen - 8; i++) {
    std::cout << EMPTY_SPACE;
  }
  std::cout << SEPARATOR << EMPTY_SPACE << "Value";

  for (int i = 0; i < valuelen - 5; i++) {
    std::cout << EMPTY_SPACE;
  }
  std::cout << "\n";

  // Display separator line
  for (int i = 0;
       i < DENOM_LENGTH + quantlen + valuelen + SEPARATOR_NUM * 2 + 1; i++) {
    std::cout << LINE;
  }
  std::cout << "\n";

  for (Coin coin : this->data->balance.balance) {
    std::cout << coin.denom;
    for (int i = 0; i < DENOM_LENGTH - std::to_string(coin.denom).size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << EMPTY_SPACE << coin.count;

    for (int i = 0; i < quantlen - std::to_string(coin.count).size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << SEPARATOR << MONEY_SYMBOL << EMPTY_SPACE;

    for (int i = 0;
         i < valuelen - Helper::floatToString(coin.getTotal(), 2).size(); i++) {
      std::cout << EMPTY_SPACE;
    }
    std::cout << Helper::floatToString(coin.getTotal(), 2) << "\n";
  }
}