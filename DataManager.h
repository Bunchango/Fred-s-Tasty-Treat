#ifndef MANAGER_H
#define MANAGER_H

#include "Balance.h"
#include "LinkedList.h"
#include <array>

#define EMPTY_SPACE " "
#define SEPARATOR "|"
#define SEPARATOR_NUM 2
#define MONEY_SYMBOL "$"
#define DENOM_LENGTH 7
#define EXCESS_LINE 4
#define LINE "-"
#define DEFAULT_QUANTITY_LENGTH 9
#define DEFAULT_VALUE_LENGTH 6

class DataManager {
private:

  // Hold the name of the files so we can save it
  std::string mealFile;
  std::string moneyFile;

public:
  /*
   * Read the money data file and meal data file into meals and balance
   * This method assumes mealFile and moneyFile are valid
   */
  LinkedList *meals;
    Balance balance;
  DataManager(std::string mealFileName, std::string moneyFileName);
  ~DataManager();

  /*
   * Save all data to data files
   * Return true if successfully saved data, false if otherwise
   */
  void save();

  /*
   * Formatted display of food items in meals
   */
  void displayMeals();

  /*
   * Formatted display of coins in balance
   */
  void displayBalance();
};

#endif // !MANAGER_H
