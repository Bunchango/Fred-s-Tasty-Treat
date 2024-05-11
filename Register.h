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
};

#endif // REGISTER_H
