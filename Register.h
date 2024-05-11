#ifndef REGISTER_H
#define REGISTER_H
#include "Coin.h"

#include <vector>
class Register {
private:
  std::vector<Coin> balance;

public:
  Register();

  /*
   * Formatted display of coins in balance
   */
  void displayBalance();

  /*
   * Pay for an item with a denomination
   * Return the amount left after paying for the cost
   * If the denomination doesn't fully cover the cost then this method will
   * return a positive number, if otherwise, it will return a negative number
   */
  int pay(int cost, int denomination);

  /*
   * Check if inputed denomination is a valid denomination
   */
  bool isDenomination(int denomination);

  /*
   * Check if balance has enough of the inputed denomination
   * It is given that the inputed denomination is valid
   */
  bool enoughDenomination(int denomination);
};

#endif // REGISTER_H
