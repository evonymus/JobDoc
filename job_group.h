#pragma once

#include "job.h"

namespace asarum {
namespace BY {

/**
* @file job.h
* @brief class keeps stores the list of all job executed as one set.
*/
class JobGroup {
public:
  std::vector<std::shared_ptr<Job>> m_jobs;
  const std::string m_group_name;

  JobGroup(const std::string &group_name);

  void addJob(const std::shared_ptr<Job> &job);
};
} // namespace BY
} // namespace asarum
