#ifndef HELPER_H
#define HELPER_H

#include "LinkedList.h"
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

// This class defines utility functions for the project,
// acknowledgements to Helper.h from Assignment 1

class Helper {
private:
  Helper();

public:
  static bool isNumber(std::string s);

  static void splitString(std::string s, std::vector<std::string> &tokens,
                          std::string delimeter);

  static std::string readInput();

  static void printInvalidInput();

  static std::string formatFloatToString(float number, int longestIntegerPart);

  static std::string floatToString(float number, int precision);

  // Get the longest integer part from a vector of floats
  static int getLongestIntegerPart(std::vector<float> numbers);

  // Check if a string can be converted to an integer
  static bool isValidInteger(std::string s);

  // Check if a string can be converted to a float
  static bool isValidFloat(std::string s);

  // Sort a vector of integer
  static void sortIntVector(std::vector<int> &v);
};
#endif
