#pragma once
#include "job.h"

/// @file job.h
/// @brief class keeps stores the list of all job executed as one set.
/// @author Marek Dziekanski

namespace asarum {
namespace BY {



const std::string HEAD_COLS[]{"LP",       "JOB_CD",   "ESC",
                              "SUB_JOBS", "NEXT_JOB", "TEMPL"};

/// @class JobGroup
/// @brief class storing vector of sequentially called jobs
class JobGroup {
public:
  /// @brief name of the group. Set with the name of the first job run as a group.
  const std::string m_group_name;

  /// @brief vector of job run as the group
  std::vector<std::shared_ptr<Job>> m_jobs;

  /// constructor
  /// @brief creates a jobs group
  /// @param group_name name of the group
  JobGroup(const std::string &group_name);

  /// @brief adds a job defintion to the group
  /// @param job pointer to the job 
  void addJob(const std::shared_ptr<Job> &job);
  
  /// @brief scans all the jobs in **m_jobs** vector and stores maximal lengths
  /// of the filds in the m_
  void getMaxFldLen();
  static bool str_compare(const std::string &a, const std::string &b);

  unsigned m_len_lp;
  unsigned m_len_job_cd;
  unsigned m_len_esc;
  unsigned m_len_sub;
  unsigned m_len_next_job;
  unsigned m_len_templ;
};
} // namespace BY
} // namespace asarum
