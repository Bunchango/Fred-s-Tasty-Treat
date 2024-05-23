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

// The DataManager is for managing all data within the system
// It will attempt to read the data from meal and coins files
// If not successful, it will create default data for the Machine
// And it is also responsible for saving the data into the files used to create
// it
class DataManager {
private:
public:
  /*
   * Read the money data file and meal data file into meals and balance
   * This method assumes mealFile and moneyFile are valid
   */
  LinkedList *meals;
  Balance *balance;
  // Hold the name of the files so we can save it
  std::string mealFile;
  std::string moneyFile;

  DataManager(std::string mealFileName, std::string moneyFileName);
  ~DataManager();

  /*
   * Save all data to data files
   */
  void save();
};

#endif // !MANAGER_H
