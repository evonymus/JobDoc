#include "asarum/BY/OdbcConnector.h"
#include <Poco/Data/ODBC/Connector.h>
#include <Poco/Data/Session.h>
#include <iostream>
#include <string>

namespace by=asarum::BY;
namespace pd=Poco::Data;

by::OdbcConnector::OdbcConnector(const char *dbName) {
    pd::ODBC::Connector::registerConnector();
    std::shared_ptr<pd::Session> session_ptr{new  pd::Session("ODBC",dbName)};
    m_session_ptr = session_ptr;
    /*
    pd::Statement select(*m_session_ptr);
    std::string id = "";
    select << "select cur_code from roe.roe ", pd::Keywords::into(id), pd::Keywords::range(0,1);
    select.execute();
    std::cout << "ID is" << id << std::endl;
    */
}


