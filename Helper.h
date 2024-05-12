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

class Helper {
private:
  Helper();

public:
  static bool isNumber(std::string s);

  static void splitString(std::string s, std::vector<std::string> &tokens,
                          std::string delimeter);

  static std::string readInput();

  static void printInvalidInput();
};
#endif
