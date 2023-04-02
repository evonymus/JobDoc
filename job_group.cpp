#include "job_group.h"

namespace by = asarum::BY;


//constructir
by::JobGroup::JobGroup(const std::string &group_name) : m_group_name(group_name){};
 
// add job to m_jobs
void by::JobGroup::addJob(const std::shared_ptr<Job> &job) {
  m_jobs.push_back(job);
}
