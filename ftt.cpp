#include "LinkedList.h"
#include "Machine.h"
#include <fstream>
#include <iostream>

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

  // Redirect all outputs to a file if specified
  std::streambuf *coutbuf = std::cout.rdbuf(); // save old buf
  if (strArgs[4] != "") {
    std::ofstream outFile(strArgs[4]);
    std::cout.rdbuf(outFile.rdbuf()); // redirect cout to file
  }

  // Redirect all outputs to a file if specified
  std::streambuf *cinbuf = std::cin.rdbuf();
  if (strArgs[3] != "") {
    std::ifstream inFile(strArgs[3]);
    std::cin.rdbuf(inFile.rdbuf());
  }

  Machine *machine = new Machine(strArgs[1], strArgs[2]);
  machine->start();
  delete machine;

  // Reset to std output and input
  std::cout.rdbuf(coutbuf);
  return EXIT_SUCCESS;
}
