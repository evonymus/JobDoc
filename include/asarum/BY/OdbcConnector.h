#pragma once
#include <memory>
#include <Poco/Data/Session.h>
#include "BaseConnector.h"
/**
 * @file  odbc_connector.h
 * @author Marek Dziekanski 
 * @brief class allowing connection with ODBC database 
 * 
 */
namespace asarum {
namespace BY {

class OdbcConnector : public BaseConnector {
public:
  /**
   * @brief Construct a new Odbc Connector object
   * 
   * @param dbName ODBC database. Use "DSN=MyConn" syntax.
   */
  OdbcConnector(const char *dbName);
  /// @brief changes the current schema.
  /// @param schema_name name of the schema
  void changeSchema(const char* schema_name);

  /// @brief changes the current schema.
  /// @param schema_name name of the schema
  void changeSchema(const std::string &r_schema_name);
};
} // namespace BY
} // namespace asarum
