#include "Machine.h"
#include "Coin.h"
#include "DataManager.h"
#include "Helper.h"
#include "Node.h"
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
      this->purchaseMeal();
    } else if (input == "3") {
      std::cout << "Save and exit";
    } else if (input == "4") {
      this->addFood();
    } else if (input == "5") {
      std::cout << "Remove food";
      this->removeFood();
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
  //print out prompt
  std::cout << "Purchase Meal\n"
               "-------------\n";
  std::cout << "Please enter the ID of the food you wish to purchase: ";

  // Check if valid ID
  bool run = false;
  bool prompt = true;
  Node *meal = nullptr;
  int priceAsCents = 0;

  while (prompt) {
    std::string mealID = Helper::readInput();
    // Check if user wants to exit
    if (std::cin.eof() || mealID.empty()) {
      std::cout << "Cancel purchase" << "\n";
      std::cin.clear(); // Clear the error flags
      // terminate loop
      run = false;
      prompt = false;
    }
    // get the selected meal by ID
    meal = this->data->meals->getById(mealID);
    // check in-stock conditions
    if (meal && meal->data->on_hand > 0 && prompt) {
      run = true;
      // denominate the price to cents
      priceAsCents = meal->data->price.valueAsDenom();
      // print out messages
      std::cout << "You have selected \"" << meal->data->name << " - "
                << meal->data->description << "\"" << ". This will cost you $ "
                << (float)priceAsCents / 100 << " .";
      std::cout << "Please hand over the money - type in the value of each "
                   "note/coin in cents."
                << "\n";
      std::cout << "Please enter ctrl-D or enter on a new line to Cancel this "
                   "purchase."
                << "\n";
      prompt = false;
    } else {
      // print out fail message when not found
      std::cout << "Item not found. Please check the food ID and try again"
                << "\n";
      std::cin.clear();
    }
  }

  // Buying phase
  // Store all coins paid by the customer
  std::vector<Coin> payings = {};
  // A bool representing that user fully paid for the item
  bool reachedToRegister = false;

  while (run) {
    if (priceAsCents > 0) {
      // If the user hasn't fully paid for the item
      std::cout << "You still need to give us: $ " << (float)priceAsCents / 100
                << ": ";
    }

    std::string input = Helper::readInput();

    // Check if user wants to exit
    if (std::cin.eof() || input.empty()) {
      std::cout << "Cancel purchase" << "\n";
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
      reachedToRegister = true;
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
        } else {
          std::cout << "Register doesn't have enough coins for change" << "\n";
          run = false;
          reachedToRegister = false; // Cancel pay
        }
        // Print the denomination
        if (maximumDenom < 100 && maxCoinPtr) {
          std::cout << maximumDenom << "c ";
        } else if (maximumDenom >= 100 && maxCoinPtr) {
          std::cout << "$" << maximumDenom / 100 << " ";
        }

        run = false;
      }
    }
  }
  // Add the coins from customer to the system

  if (reachedToRegister) {
    for (Coin coin : payings) {
      this->data->balance->insert(coin);
    }
    // Decrement the amount
    meal->data->on_hand--;
  }
}

void Machine::displayMeals() {
  this->data->meals->sortByAlpha();
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

void Machine::addFood() {
  std::string mealID = FoodItem::constructID(this->data->meals->getNextId());
  std::string itemName = "";
  std::string itemDesc = "";
  std::string itemPrice = "";

  // booleans to manage the flow
  bool name = false;
  bool desc = false;
  bool price = false;
  bool success = false;

  if (mealID.size() == IDLEN) {
    name = true;
    std::cout << "This new meal item will have the Item ID of " << mealID
              << ".\n";
  }

  while (name) {
    std::cout << "Enter the item name: ";
    itemName = Helper::readInput();
    if (std::cin.eof()) {
      std::cout << "Cancel add" << "\n";
      std::cin.clear();
      name = false;
    }

    if (name && itemName.size() > NAMELEN) {
      std::cout << "Name too long." << "\n";
    } else if (name && itemName.size() < NAMELEN) {
      name = false;
      desc = true;
    }
  }

  while (desc) {
    std::cout << "Enter the item description: ";
    itemDesc = Helper::readInput();

    if (std::cin.eof()) {
      std::cout << "Cancel add" << "\n";
      std::cin.clear();
      desc = false;
    }

    if (desc && itemDesc.size() > DESCLEN) {
      std::cout << "Description too long." << "\n";
    } else if (desc && itemDesc.size() < DESCLEN) {
      desc = false;
      price = true;
    }
  }

  while (price) {
    std::cout << "Enter the price for this item (in cents): ";
    itemPrice = Helper::readInput();

    if (std::cin.eof()) {
      std::cout << "Cancel add" << "\n";
      std::cin.clear();
      price = false;
    }

    if (price && !Price::isValidPrice(itemPrice)) {
      std::cout << "Invalid price" << "\n";
    } else if (price && Price::isValidPrice(itemPrice)) {
      price = false;
      success = true;
    }
  }

  // Create FoodItem obj and assign it to LinkedList
  if (success) {
    std::vector<std::string> prices = {};
    Helper::splitString(itemPrice, prices, ".");
    Price price = Price();
    price.dollars = std::stoi(prices[0]);
    price.cents = std::stoi(prices[1]);

    FoodItem *newMeal = new FoodItem(mealID, itemName, itemDesc, price);
    Node *newNode = new Node();
    newNode->data = newMeal;
    this->data->meals->append(newNode);

    std::cout << "This item \"" << itemName << " - " << itemDesc << "\""
              << "has now been added to the food menu" << "\n";
  }
}

void Machine::removeFood() {}