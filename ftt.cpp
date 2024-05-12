#include "LinkedList.h"
#include <iostream>
#include <vector>

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv) {
  // Read arguments into an array of strings
  // Use an array of size 6 as at most there will only be 6 arg strings
  // (including EOF)
  std::string strArgs[6];
  for (int i = 0; i < argc; i++) {
    std::string strArg(argv[i]);
    strArgs[i] = strArg;
  }

  return EXIT_SUCCESS;
}
