#include "Helper.h"
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
  std::string strArgs[6];
  for (int i = 0; i < argc; i++) {
    std::string strArg(argv[i]);
    strArgs[i] = strArg;
  }

  // Redirect all outputs to a file if specified
  std::streambuf *coutbuf = std::cout.rdbuf(); // save old buf
  std::ofstream outFile;
  if (strArgs[4] != "") {
    outFile.open(strArgs[4]);
    std::cout.rdbuf(outFile.rdbuf()); // redirect cout to file
  }

  // Read all inputs from a file if specified
  std::streambuf *cinbuf = std::cin.rdbuf();
  std::ifstream inFile;
  if (strArgs[3] != "") {
    inFile.open(strArgs[3]);
    std::cin.rdbuf(inFile.rdbuf());
  }

  Machine *machine = new Machine(strArgs[1], strArgs[2]);
  machine->start();
  delete machine;

  // Reset to std output and input
  std::cout.rdbuf(coutbuf);

  // Close file streams
  if (outFile.is_open()) {
    outFile.close();
  }
  if (inFile.is_open()) {
    inFile.close();
  }

  return EXIT_SUCCESS;
}
