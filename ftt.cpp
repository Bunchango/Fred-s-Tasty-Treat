#include "Helper.h"
#include "Machine.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

int main(int argc, char **argv) {
  // Read arguments into an array of strings
  if (argc <= 5 && argc >= 3) {
    std::string strArgs[5];
    for (int i = 0; i < argc; i++) {
      std::string strArg(argv[i]);
      strArgs[i] = strArg;
    }

    Machine *machine = new Machine(strArgs[1], strArgs[2]);
    machine->start();
    delete machine;
  } else {
    std::cout << "Invalid arguments" << "\n";
  }

  return EXIT_SUCCESS;
}
