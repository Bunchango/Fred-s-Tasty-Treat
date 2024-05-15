#include "helper.h"
#include "Helper.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Helper::Helper() {}

void Helper::printInvalidInput() {
  std::cout << "Invalid input.\n" << std::endl;
}

// This below function does not comply to our C++ Style Guide,
// as it uses the banned keyword "break" twice. The marker will
// not deduct marks in this case if you use this function, though
// this is not ideal. Nevertheless, feel free to revise this
// function to make it complied to style guide (this is optional).
bool Helper::isNumber(std::string s) {
  std::string::const_iterator it = s.begin();
  char dot = '.';
  int nb_dots = 0;
  while (it != s.end()) {
    if (*it == dot) {
      nb_dots++;
      if (nb_dots > 1) {
        break;
      }
    } else if (!isdigit(*it)) {
      break;
    }

    ++it;
  }
  return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(std::string s, std::vector<std::string> &tokens,
                         std::string delimeter) {
  tokens.clear();
  char *_s = new char[s.length() + 1];
  strcpy(_s, s.c_str());

  char *pch;
  pch = strtok(_s, delimeter.c_str());
  while (pch != NULL) {
    tokens.push_back(pch);
    pch = strtok(NULL, delimeter.c_str());
  }
  delete[] _s;
}

std::string Helper::readInput() {
  std::string input;
  std::getline(std::cin, input);

  std::cout << std::endl;

  return input;
}

std::string Helper::floatToString(float value, int precision) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << value;
  return oss.str();
}

int Helper::getLongestIntegerPart(std::vector<float> numbers) {
  int longestInteger = 0;

  for (float num : numbers) {
    std::vector<std::string> splitted = {};
    std::string numStr = floatToString(num, 2);
    Helper::splitString(numStr, splitted, ".");

    if (splitted[0].size() > longestInteger) {
      longestInteger = splitted[0].size();
    }
  }

  return longestInteger;
}

std::string Helper::formatFloatToString(float number, int longestIntegerPart) {
  std::string result = "";
  std::vector<std::string> splitNumber = {};
  splitString(floatToString(number, 2), splitNumber, ".");

  if (splitNumber[0].size() < longestIntegerPart) {
    for (int i = 0; i < longestIntegerPart - splitNumber[0].size(); i++) {
      result.append(" ");
    }
  }
  result.append(splitNumber[0]);
  result.append(".");
  result.append(splitNumber[1]);

  return result;
}

bool Helper::isValidInteger(std::string s) {
  std::istringstream iss(s);
  int num;
  return (iss >> num) && iss.eof();
}

bool Helper::isValidFloat(std::string s) {
  std::istringstream iss(s);
  float num;
  return isNumber(s) && (s.find(".") != std::string::npos) &&
         ((iss >> num) && iss.eof());
}
