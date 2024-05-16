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
    this->data->displayMeals();
  } else if (input == "2") {
    std::cout << "Purchase Meal\n"
                 "-------------\n"
                 "Please enter the ID of the food you wish to purchase: ";
  } else if (input == "3") {
    std::cout << "Save and exit";
  } else if (input == "4") {
    std::cout << "Add food";
  } else if (input == "5") {
    std::cout << "Remove food";
  } else if (input == "6") {
    this->data->displayBalance();
  } else if (input == "7") {
    std::cout << "Abort";
  } else {
    Helper::printInvalidInput();
  }
}
