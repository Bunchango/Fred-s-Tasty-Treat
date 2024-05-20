#ifndef MANAGER_H
#define MANAGER_H

#include "Balance.h"
#include "LinkedList.h"
#include <array>

#define EMPTY_SPACE " "
#define SEPARATOR "|"
// Representing the number of separators to display the meals and balance
#define SEPARATOR_NUM 2
#define MONEY_SYMBOL "$"
#define DENOM_LENGTH 7
// The extra padding of LINEs
#define EXCESS_LINE 4
#define LINE "-"
#define DEFAULT_QUANTITY_LENGTH 9
// This is for dynamically printing out the values of balance
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
  Balance *balance;
  DataManager(std::string mealFileName, std::string moneyFileName);
  ~DataManager();

  /*
   * Save all data to data files
   */
  void save();
};

#endif // !MANAGER_H
