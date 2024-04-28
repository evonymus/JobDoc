#pragma once
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
  /**
   * @brief Construct a new Odbc Connector object
   * 
   * @param dbName ODBC database. Use "DSN=MyConn" syntax.
   */
  OdbcConnector(const char *dbName);
};
} // namespace BY
} // namespace asarum
