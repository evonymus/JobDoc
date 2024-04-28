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
#include "job_group.h"
#include <Poco/Data/Session.h>
#include <memory>

namespace asarum {
namespace BY {
class SQLiteConnector {
public:
 /**
  * @brief Construct a new SQLiteConnector object
  * 
  * @param dbName name of the file with SQLite database
  */
  SQLiteConnector(const char *dbName);
  void getJobs(std::vector<std::shared_ptr<JobGroup>> &job_groups);

private:
  std::shared_ptr<Poco::Data::Session> m_session_ptr;
  void init();
  void shutDown();
};
} // namespace BY
} // namespace asarum
