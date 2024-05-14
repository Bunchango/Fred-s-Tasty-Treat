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

    static std::string formatFloatToString(float number, int longestIntegerPart);

    static std::string floatToString(float number);

    // Get the longest integer part from a vector of floats
    static int getLongestIntegerPart(std::vector<float> numbers);

    // Get the first two character of a string
    static std::string extractFirstTwoNumbers(const std::string &input);
};
#endif