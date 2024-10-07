#include "asarum/BY/SQLiteConnector.h"
#include "asarum/BY/sql_queries.h"
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <iostream>
#include <memory>
#include <string>

namespace by = asarum::BY;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;

by::SQLiteConnector::SQLiteConnector(const char *dbName) {
  try {
    init();
    std::shared_ptr<Session> session_{new Session("SQLite", dbName)};
    m_session_ptr = session_;
  } catch (Poco::Exception &ex) {
    std::cout << "Could not connect to the database " << dbName
              << ", reason: " << ex.displayText() << std::endl;
    throw ex;
  }
}


//************************ PRIVATE *****************************

void by::SQLiteConnector::init() { SQLite::Connector::registerConnector(); }

void by::SQLiteConnector::shutDown() {
  SQLite::Connector::unregisterConnector();
}
