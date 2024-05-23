#ifndef COIN_H
#define COIN_H
#include <string>

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM "," // delimiter

// enumeration representing the various types of currency available in the
// system.
enum Denomination {
  FIVE_CENTS = 5,
  TEN_CENTS = 10,
  TWENTY_CENTS = 20,
  FIFTY_CENTS = 50,
  ONE_DOLLAR = 100,
  TWO_DOLLARS = 200,
  FIVE_DOLLARS = 500,
  TEN_DOLLARS = 1000,
  TWENTY_DOLLARS = 2000,
  FIFTY_DOLLARS = 5000,
};

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin {
public:
  // the denomination type
  enum Denomination denom;

  // the count of how many of these are in the cash register
  unsigned count;

  /*
   * Check if inputed denomination is a valid denomination
   */
  bool static isDenomination(std::string denomination);

  /*
   * Return a Denomination enum corresponding to an int
   * This function assumes the value is a valid denomination
   */
  Denomination static intToDenomination(int denomination_val);

  /*
   * Get the total value of this Coin
   */
  float getTotal();
};

#endif // COIN_H
