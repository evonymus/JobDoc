#pragma once
#include <memory>
#include <Poco/Data/Session.h>
/**
 * @file  odbc_connector.h
 * @author Marek Dziekanski 
 * @brief class allowing connection with ODBC database 
 * 
 */
namespace asarum {
namespace BY {

class OdbcConnector {
public:
  /// @brief pointer to Poco::Data::Session object;
  std::shared_ptr<Poco::Data::Session> m_session_ptr;

  /**
   * @brief Construct a new Odbc Connector object
   * 
   * @param dbName ODBC database. Use "DSN=MyConn" syntax.
   */
  OdbcConnector(const char *dbName);
};
} // namespace BY
} // namespace asarum
