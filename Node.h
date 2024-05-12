#ifndef NODE_H
#define NODE_H
#include "Coin.h"
#include <string>

// The length of the id string not counting the nul terminator
#define IDLEN 5

// The maximum length of a food item name not counting the nul terminator
#define NAMELEN 40

// The maximum length of a food item description not counting the nul
// terminator.
#define DESCLEN 255

// The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

// The possible default food stock level that all new stock should start at and
// that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

// The number of denominations of currency available in the system
#define NUM_DENOMS 8

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price {
public:
  // The dollar value, and the cents value for some price
  unsigned dollars, cents;
};

/**
 * data structure to represent a food item within the system
 **/
class FoodItem {
public:
  // the unique id for this food item
  std::string id;

  // the name of this food item
  std::string name;

  // the description of this food item
  std::string description;

  // the price of this food item
  Price price;

  // how many of this food item do we have on hand?
  unsigned on_hand;

  // For now, on_hand takes the default value
  FoodItem(std::string id, std::string name, std::string description,
           Price price);
};

/**
 * the node that holds the data about a food item stored in memory
 **/
class Node {
public:
  // Assume that when we first create a Node, it doesn't hold any data, the
  // LinkedList object is responsble for setting the data of the Node
  Node();
  ~Node();
  // pointer to the data held for the node
  FoodItem *data;
  // pointer to the next node in the list
  Node *next;
};

#endif // NODE_H
