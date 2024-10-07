#include "asarum/BY/JobDefGetter.h"
#include <Poco/ActiveRecord/Query.h>
#include <exception>
#include <unordered_set>

namespace by = asarum::BY;
namespace pd = Poco::Data;
namespace pa = Poco::ActiveRecord;
using namespace std;

/// @brief maximal number of child jobs. Used to react in case jobs are
/// infinitely looping.
constexpr unsigned MAX_CHILDREN_COUNT = 1000;

by::JobDefGetter ::JobDefGetter(
    std::shared_ptr<Poco::Data::Session> session_ptr) {
  m_session_ptr = session_ptr;
  m_context_ptr = new pa::Context(*m_session_ptr);
}

/***************************************************************/

/// @brief  Gets vector with the Jobs defintion
/// @return vector of Poco::AutoPtr pointers to JobDef objects
vector<Poco::AutoPtr<by::JobDef>> by::JobDefGetter::getAllJobDefs() {
  pa::Query<by::JobDef> query{m_context_ptr};
  vector<Poco::AutoPtr<by::JobDef>> result =
      query.orderBy("job_cd ASC").execute();
  return result;
}

/***************************************************************/

/// @brief returns pointer to the jobs which name is given as the parameter
/// @param job_name name of the job
/// @return Poco::AutoPtr pointer to the job
Poco::AutoPtr<asarum::BY::JobDef>
asarum::BY::JobDefGetter::getJobDef(const char *job_name) {
  return by::JobDef::find(m_context_ptr, job_name);
}

/***************************************************************/
vector<Poco::AutoPtr<by::EntySelCta>> by::JobDefGetter::getAllEntySelCtas() {
  pa::Query<by::EntySelCta> query{m_context_ptr};
  return query.execute();
}
/***************************************************************/
std::vector<Poco::AutoPtr<by::AdtnData>>
asarum::BY::JobDefGetter::getAllAdtnTemplates() {
  pa::Query<by::AdtnData> query(m_context_ptr);
  return query.where("ADTN_DATA_CD IS NOT NULL").execute();
}

//**************************************************************

std::vector<Poco::AutoPtr<asarum::BY::JobSelCta>>
asarum::BY::JobDefGetter::getJobSelCtas(const Poco::AutoPtr<JobDef> job_ptr) {
  Poco::ActiveRecord::Query<by::JobSelCta> query(job_ptr->context());
  const std::string where = "job_cd ='" + job_ptr->id() + "'";
  const auto result = query.where(where).execute();
  return result;
}

//**************************************************************
std::vector<Poco::AutoPtr<by::JobSelCta>>
asarum::BY::JobDefGetter::getAllJobSelCtas() {
  pa::Query<by::JobSelCta> query(m_context_ptr);
  return query.execute();
}

//**************************************************************

std::vector<Poco::AutoPtr<by::SchdDetl>>
asarum::BY::JobDefGetter::getAllSchdDetls() {
  pa::Query<by::SchdDetl> query(m_context_ptr);
  return query.execute();
}

/***************************************************************/
std::unique_ptr<by::EscMap> asarum::BY::JobDefGetter::getEscMap() {
  std::unique_ptr<EscMap> esc_map{new EscMap()};
  auto job_esc_vect = getAllJobSelCtas();
  for (const auto i : job_esc_vect) {
    (*esc_map)[i->job_cd()->id()] = i->enty_sel_cta_cd();
  }
  return esc_map;
}
by::JobDefGetter::~JobDefGetter() {}

/*********************** PRIVATE MEMBERS ******************************/
/// @brief  Gets vector with the Jobs defintion
/// @return vector of Poco::AutoPtr pointers to JobDef objects
vector<Poco::AutoPtr<by::JobDef>> by::JobDefGetter::getScheduledJobDefs() {
  pa::Query<by::JobDef> query{m_context_ptr};
  vector<Poco::AutoPtr<by::JobDef>> result =
      query.where("schd_detl_id is NOT null").execute();
  return result;
}

//**************************************************************

/// @brief functions iterates through all jobs using next_job_success and adds
/// all found records to r_result vector
/// @param job_ptr root job
/// @param r_result vector to which there are added jobs
void by::JobDefGetter::getChildJobs(const by::JobDef::Ptr job_ptr,
                                    std::vector<by::JobDef::Ptr> &r_result) {
  unsigned count = 0;
  std::unordered_set<std::string> inserted_jobs_{};
  by::JobDef::Ptr current_job = job_ptr;
  // if next_job_cd exists, and the jobs is not already in the vector
  while (current_job != nullptr && inserted_jobs_.find(current_job->id()) == inserted_jobs_.end()) 
         {
    r_result.push_back(current_job);

    if (current_job != nullptr) {
      inserted_jobs_.insert(current_job->id());
    }
    current_job = current_job->next_job_cd_success();
    count++;
    if (count > MAX_CHILDREN_COUNT) {
      throw runtime_error("Too many children exception");
    }
  }
}

//**************************************************************

/// @brief functions iterates through all jobs using next_job_success and adds
/// all found records to r_result vector
/// @param job_name name of the root job
/// @param r_result vector to which there are added jobs
void by::JobDefGetter::getChildJobs(const char *job_name,
                                    std::vector<by::JobDef::Ptr> &r_result) {
  static unsigned count = 0;
  // calling find method to get the job
  by::JobDef::Ptr job_ptr = by::JobDef::find(m_context_ptr, job_name);
  getChildJobs(job_ptr, r_result);
}
