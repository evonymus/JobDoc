#pragma once
#include "job_group.h"
#include <Poco/Data/Session.h>
#include <memory>

namespace asarum {
namespace BY {
class SQLiteConnector {
public:
  SQLiteConnector(const char *dbName);
  void getJobs(std::vector<std::shared_ptr<JobGroup>> &job_groups);

private:
  std::shared_ptr<Poco::Data::Session> m_session_ptr;
  void init();
  void shutDown();
};
} // namespace BY
} // namespace asarum
