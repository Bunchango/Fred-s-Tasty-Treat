#ifndef BALANCE_H
#define BALANCE_H
#include "Coin.h"
#include "Node.h"

#include <vector>
class Balance {
public:
  // We only need a fixed size array of Coin as balance won't change size during
  // runtime
  Coin balance[NUM_DENOMS];

  Balance();

  /*
   * Pay for an item with a denomination
   * Return the amount left after paying for the cost
   * If the denomination doesn't fully cover the cost then this method will
   * return a positive number, if otherwise, it will return a negative number
   */
  int pay(int cost, int denomination);

  /*
   * Check if balance has enough of the inputed denomination
   * It is given that the inputed denomination is valid
   */
  bool enoughDenomination(int denomination);

  /*
   * Add quantity to a denomination
   */
  void insert(Coin coin);
};

#endif // BALANCE_H
