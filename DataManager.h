#ifndef MANAGER_H
#define MANAGER_H
#include "Coin.h"
#include "LinkedList.h"
#include <string>
#include <vector>

class DataManager {
private:
  std::string foodFile;
  std::string moneyFile;

public:
  /*
   * Read a file and pass the food data to foodList, it is the programmer
   * responsible to ensure the food file is in correct format Return true if
   * successfully read, false if otherwise
   */
  static bool readFoodFile(std::string fileName, LinkedList *foodList);

  /*
   * Read a file and pass money data to balance vector, it is programmer
   * responsible to ensure the money file is in correct format Return true if
   * successfully read, false if otherwise
   */
  static bool readMoneyFile(std::string fileName, std::vector<Coin> *balance);

  /*
   * Save LinkedList data into food file
   * return true if successfully saved, false if otherwise
   */
  static bool saveFoodFile(LinkedList *foodList);

  /*
   * Save balance vector into money file
   * return true if successfully saved, false if otherwise
   */
  static bool saveMoneyFile(std::vector<Coin> *balance);
};

#endif // !MANAGER_H
