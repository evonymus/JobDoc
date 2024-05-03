#include <exception>
#include <iostream>
#include <string>

#include "asarum/BY/menu.h"
#include "test.h"
namespace by = asarum::BY;

int main(int argc, char *argv[]) {
  try {
    //by::OdbcConnector ocon{"DSN=ROE"};
    Test test;
    test.runTest();
    return 0;

    by::Menu menu(argc, argv);
    menu.handleMenu();

  } catch (std::exception &ex) {
    std::cout << "exception thrown: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "unexpected exception, closing the program \n";
  }
  return 0;
}
