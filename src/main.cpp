#include <iostream>
#include <string>
#include <exception>

#include "menu.h"
namespace by = asarum::BY;

int main(int argc, char *argv[]) {
  try {
    by::Menu menu(argc, argv); 
    menu.handleMenu();

  } 
  catch(std::exception &ex) {
    std::cout << "exception thrown: " << ex.what() << std::endl;
  }
  catch (...) {
    std::cout << "unexpected exception, closing the program \n";
  }
  return 0;
}
