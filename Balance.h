#ifndef BALANCE_H
#define BALANCE_H
#include "Coin.h"
#include "Node.h"
#include <vector>

// This class is responsible for managing all Coins within the system
class Balance {
public:
  // We only need a fixed size array of Coin as balance won't change size during
  // runtime
  Coin balance[NUM_DENOMS];

  Balance();

  /*
   * Check if balance has enough of the inputed denomination
   * It is given that the inputed denomination is valid
   */
  bool enoughDenomination(int denomination);

  /*
   * Add quantity to a denomination
   */
  void insert(Coin newCoin);

  /*
   * Get the maximum quantity of all denomination
   */
  int getMaxQuantity();

  /*
   * Get the maximum value of all denomination
   */
  float getMaxValue();

  /*
   * Get the Coin corressponding with a denom enum
   */
  Coin *getDenom(int denom);

  /*
   * Get the maximum denom available to pay of a value
   */
  Coin *getMaxDenomForValue(int value);

  float getTotalValue();
};

#endif // BALANCE_H
