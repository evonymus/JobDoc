#include <exception>
#include <iostream>
#include <string>

#include "asarum/BY/menu.h"
#include "test.h"
namespace by = asarum::BY;

/// @brief Jobdoc, the program to document, backup, and restore TMS jobs
/// @details The program allows to create documentation and SQL scripts
/// with defintions of jobs using either, and ODBC connection or a backup
/// of jobs written as SQLite database.
/// @author Marek Dziekanski 2024-05-16

constexpr int ERROR_INVALID_ARGUMENT = -1;
constexpr int ERROR_GENERAL_EXCEPTION = -2;

int main(int argc, char *argv[])
{
  try
  {
    // by::OdbcConnector ocon{"DSN=ROE"};
     //Test test;
     //test.runTest();
     //return 0;

    by::Menu menu(argc, argv);
    menu.handleMenu();
  }
  catch(std::invalid_argument &ex) {
    std::cout << "\n program was called with invalid arguments: " << ex.what() << '\n';
    return ERROR_INVALID_ARGUMENT;
  }
  catch (std::exception &ex)
  {
    std::cout << "exception thrown: " << ex.what() << std::endl;
    return ERROR_GENERAL_EXCEPTION;
  }
  catch (...)
  {
    std::cout << "unexpected exception, closing the program \n";
    return ERROR_GENERAL_EXCEPTION;
  }
  return 0;
}
