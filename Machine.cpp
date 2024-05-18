#include "Machine.h"
#include "Coin.h"
#include "DataManager.h"
#include "Helper.h"
#include "iostream"
#include <string>
#include <vector>

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
      purchaseMeal();
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
      std::cin.clear();
    }
    std::cout << "\n";
  }
}

void Machine::purchaseMeal() {
  std::string mealID = Helper::readInput();
  // Check if valid ID
  bool run = false;
  Node *meal = this->data->meals->getById(mealID);
  int priceAsCents = 0;

  if (meal) {
    run = true;
    priceAsCents = meal->data->price.valueAsDenom();
    std::cout << "You have selected \"" << meal->data->name << " - "
              << meal->data->description << "\"" << ". This will cost you $ "
              << (float)priceAsCents / 100 << " .";
    std::cout << "Please hand over the money - type in the value of each "
                 "note/coin in cents."
              << "\n";
    std::cout
        << "Please enter ctrl-D or enter on a new line to cancel this purchase."
        << "\n";
  } else {
    std::cout << "ID does not exist" << "\n";
    std::cin.clear();
  }

  // Buying phase
  // Store all coins paid by the customer
  std::vector<Coin> payings = {};

  while (run) {
    if (priceAsCents > 0) {
      // If the user hasn't fully paid for the item
      std::cout << "You still need to give us: $ " << (float)priceAsCents / 100
                << ": ";
    }

    std::string input = Helper::readInput();

    // Check if user wants to exit
    if (std::cin.eof() || input.empty()) {
      std::cout << "Cancle purchase" << "\n";
      std::cin.clear(); // Clear the error flags
      run = false;
    } else if (Coin::isDenomination(input)) {
      int pay = std::stoi(input);
      priceAsCents -= pay;

      // Add new coins to the system, relook at this, only add after the user
      // fully paid for the items
      Coin newCoin = Coin();
      newCoin.count = 1;
      newCoin.denom = Coin::intToDenomination(std::stoi(input));
      payings.push_back(newCoin);
    } else {
      std::cout << "Error: invalid denomination encountered" << "\n";
      std::cin.clear();
    }

    if (priceAsCents <= 0) {
      // Get the change
      std::cout << "Your change is ";
      int change = -priceAsCents; // Make it positive for easier handling
      while (change > 0) {
        int maximumDenom = 0;
        Coin *maxCoinPtr = nullptr;

        // Find the largest denomination coin that can be used for the change
        for (Coin &coin : this->data->balance->balance) {
          if (coin.count > 0 && coin.denom <= change &&
              coin.denom > maximumDenom) {
            maximumDenom = coin.denom;
            maxCoinPtr = &coin;
          }
        }

        // Decrement the coin count
        if (maxCoinPtr) {
          maxCoinPtr->count--;
          change -= maximumDenom;
        }
        // Print the denomination
        if (maximumDenom < 100) {
          std::cout << maximumDenom << "c ";
        } else {
          std::cout << "$" << maximumDenom / 100 << " ";
        }

        run = false;
      }
    }
  }
  // Add the coins from customer to the system
  for (Coin coin : payings) {
    this->data->balance->insert(coin);
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
  int longestInteger =
      Helper::getLongestIntegerPart(this->data->meals->getPrices());
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
  int quantlen =
      Helper::floatToString(this->data->balance->getMaxValue(), 0).size();
  int valuelen =
      Helper::floatToString(this->data->balance->getMaxValue(), 2).size();

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

  for (Coin coin : this->data->balance->balance) {
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