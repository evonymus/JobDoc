#include "asarum/BY/OdbcConnector.h"
#include <Poco/Data/ODBC/Connector.h>
#include <Poco/Data/Session.h>
#include <iostream>
#include <string>

namespace by=asarum::BY;
namespace pd=Poco::Data;

by::OdbcConnector::OdbcConnector(const char *dbName) {
    try {
    pd::ODBC::Connector::registerConnector();
    std::shared_ptr<pd::Session> session_ptr{new  pd::Session("ODBC",dbName)};
    m_session_ptr = session_ptr;
    if(session_ptr->isConnected()) {
        std::cout << "\nODBC Connected";
    } else {
        std::cout << "\nODBC NOT connected";
    }
    } catch(Poco::Exception &ex) {
        std::cout << "\nConnection  to " << dbName << " failed ";
        std::cout << ex.what() << '\n';
        throw;
    }
    /*
    pd::Statement select(*m_session_ptr);
    std::string id = "";
    select << "select cur_code from roe.roe ", pd::Keywords::into(id), pd::Keywords::range(0,1);
    select.execute();
    std::cout << "ID is" << id << std::endl;
    */
}

void asarum::BY::OdbcConnector::changeSchema(const char * schema_name)
{
    const std::string sql="alter session set current_schema =" + std::string(schema_name) + std::string(";");
    execSQL(sql.c_str());
}

/// @brief wrapper to allow using std::string arguments
/// @param r_schema_name 
void asarum::BY::OdbcConnector::changeSchema(const std::string & r_schema_name)
{
    changeSchema(r_schema_name.c_str());
}


