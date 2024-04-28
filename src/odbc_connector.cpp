#include "odbc_connector.h"
#include <Poco/Data/ODBC/Connector.h>
#include <Poco/Data/Session.h>
#include <iostream>
#include <string>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
namespace by=asarum::BY;

by::OdbcConnector::OdbcConnector(const char *dbName) {
    Poco::Data::ODBC::Connector::registerConnector();
    std::cout << "before session\n";
    Session session("ODBC",dbName);
    std::cout << "after session\n";
    Statement select(session);
    std::string id = "";
    select << "select cur_code from roe.roe ", into(id), range(0,1);
    select.execute();
    std::cout << "ID is" << id << std::endl;
}


