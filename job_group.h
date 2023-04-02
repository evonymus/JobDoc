#pragma once

#include "job.h"

namespace asarum {
namespace BY {


/**
* @file job.h
* @brief class keeps stores the list of all job executed as one set.
*/
const std::string HEAD_COLS[]{"LP", "ESC", "JOB_CD", "SUB_JOBS", "NEXT_JOB", "TEMPL"};
class JobGroup {
public:

  const std::string m_group_name;
  std::vector<std::shared_ptr<Job>> m_jobs;

  JobGroup(const std::string &group_name);

  void addJob(const std::shared_ptr<Job> &job);
  void getMaxFldLen(); 
  static bool str_compare(const std::string& a, const std::string& b);

  unsigned m_len_lp;
  unsigned m_len_job_cd;
  unsigned m_len_esc;
  unsigned m_len_sub;
  unsigned m_len_next_job;
  unsigned m_len_templ;
};
} // namespace BY
} // namespace asarum
