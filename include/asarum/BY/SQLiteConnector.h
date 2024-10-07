#pragma once

/**
 * @file sqlite_connector.h
 * @author Marek Dziekanski
 * @brief Allows connection to a SQLite database
 * @version 0.1
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "BaseConnector.h"
#include <Poco/Data/Session.h>
#include <memory>

namespace asarum {
namespace BY {
class SQLiteConnector : public BaseConnector {
public:
  /**
   * @brief Construct a new SQLiteConnector object
   *
   * @param dbName name of the file with SQLite database
   */
  SQLiteConnector(const char *dbName);

private:
  void init();
  void shutDown();
};
} // namespace BY
} // namespace asarum
