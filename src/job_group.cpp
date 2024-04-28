#include "job_group.h"
#include <algorithm>
#include <iostream>
#include <memory>
namespace by = asarum::BY;
constexpr unsigned MAX_LEN_FIELDS = 4;
constexpr unsigned MIN_CELL_LENGTH = 5;

/// constructor
/// @param group_name setting the name for the group. 
/// here the name of the job having a schedule set.
by::JobGroup::JobGroup(const std::string &group_name)
    : m_group_name(group_name) {

  m_len_lp = HEAD_COLS[0].size();
  m_len_job_cd = HEAD_COLS[1].size();
  m_len_esc = HEAD_COLS[2].size();
  m_len_sub = HEAD_COLS[3].size();
  m_len_next_job = HEAD_COLS[4].size();
  m_len_templ = HEAD_COLS[5].size();
}

/// add job to m_jobs vector
/// @param job reference to shared_ptr<Job> that is to be added to the group
void by::JobGroup::addJob(const std::shared_ptr<Job> &job) {
  m_jobs.push_back(job);
}

/// @brief get max lenght of all fields in Job objects and
/// store the values in memer fields of the class
void by::JobGroup::getMaxFldLen() {
  for (const auto &jb : m_jobs) {
    if (!jb->m_job_cd.empty()) {

      m_len_job_cd = jb->m_job_cd.size() > m_len_job_cd ? jb->m_job_cd.size()
                                                        : m_len_job_cd;
    }
    m_len_esc = jb->m_esc.size() > m_len_esc ? jb->m_esc.size() : m_len_esc;
    m_len_templ =
        jb->m_templ.size() > m_len_templ ? jb->m_templ.size() : m_len_templ;
    m_len_next_job = jb->m_next_job_success.size() > m_len_next_job
                         ? jb->m_next_job_success.size()
                         : m_len_next_job;

    // getting the length of the longes sub-job
    if (!jb->m_sub_jobs_list.empty()) {
      auto len_sub_job_ =
          *std::max_element(jb->m_sub_jobs_list.begin(),
                            jb->m_sub_jobs_list.end(), JobGroup::str_compare);
      m_len_sub =
          len_sub_job_.size() > m_len_sub ? len_sub_job_.size() : m_len_sub;
    }
  }
}

bool by::JobGroup::str_compare(const std::string &a, const std::string &b) {
  return a.size() < b.size();
}
