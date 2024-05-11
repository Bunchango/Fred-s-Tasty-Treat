#include "LinkedList.h"
#include <iostream>

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv) {
  // Get arguments
  for (int i = 0; i < argc; i++) {
    std::string strArgv(argv[i]);
    std::cout << strArgv << "\n";
  }

  return EXIT_SUCCESS;
}
