#ifndef MANAGER_H
#define MANAGER_H

#include "LinkedList.h"
#include "Register.h"
class DataManager {
private:
  LinkedList *meals;
  Register balance;
  // Hold the name of the files so we can save it
  std::string mealFile;
  std::string moneyFile;

public:
  /*
   * Read the money data file and meal data file into meals and balance
   * This method assumes mealFile and moneyFile are valid
   */
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
