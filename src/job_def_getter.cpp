#include "asarum/BY/job_def_getter.h"
#include <Poco/ActiveRecord/Query.h>
#include <exception>

namespace by=asarum::BY;
namespace pd=Poco::Data;
namespace pa=Poco::ActiveRecord;
using namespace std;

/// @brief maximal number of child jobs. Used to react in case jobs are infinitely looping.
constexpr unsigned MAX_CHILDREN_COUNT = 100;

by::JobDefGetter ::JobDefGetter(std::shared_ptr<Poco::Data::Session> session_ptr)   {
        m_session_ptr = session_ptr;
        m_context_ptr = new pa::Context(*m_session_ptr);
}

/// @brief  Gets vector with the Jobs defintion
/// @return vector of Poco::AutoPtr pointers to JobDef objects 
vector<Poco::AutoPtr<by::JobDef>> by::JobDefGetter::getAllJobDefs() {
    pa::Query<by::JobDef> query{m_context_ptr};
    vector<Poco::AutoPtr<by::JobDef>> result = query
    .where("schd_detl_id is NOT null")
    .execute();
    return result;
}

/// @brief returns pointer to the jobs which name is given as the parameter
/// @param job_name name of the job 
/// @return Poco::AutoPtr pointer to the job 
Poco::AutoPtr<asarum::BY::JobDef> asarum::BY::JobDefGetter::getJobDef(const char *job_name)
{
    return by::JobDef::find(m_context_ptr, job_name);
}
vector<Poco::AutoPtr<by::JobSelCta>> by::JobDefGetter::getJobSelCtas() {
    pa::Query<by::JobSelCta> query{m_context_ptr};
    return query.execute();
}

vector<Poco::AutoPtr<by::EntySelCta>> by::JobDefGetter::getEntySelCtas() {
    pa::Context::Ptr pContext = new pa::Context(*m_session_ptr);  
    pa::Query<by::EntySelCta> query{m_context_ptr};
    return query.execute();
}
    
by::JobDefGetter::~JobDefGetter() { }

/*********************** PRIVATE MEMBERS ******************************/
/// @brief  Gets vector with the Jobs defintion
/// @return vector of Poco::AutoPtr pointers to JobDef objects 
vector<Poco::AutoPtr<by::JobDef>> by::JobDefGetter::getScheduledJobDefs() {
    pa::Query<by::JobDef> query{m_context_ptr};
    vector<Poco::AutoPtr<by::JobDef>> result = query
    .where("schd_detl_id is NOT null")
    .execute();
    return result;
}

/// @brief functions iterates through all jobs using next_job_success and adds all found records to r_result vector
/// @param job_ptr root job 
/// @param r_result vector to which there are added jobs 
void by::JobDefGetter::getChildJobs(const by::JobDef::Ptr job_ptr, std::vector<by::JobDef::Ptr> &r_result){
    static unsigned count = 0;
    by::JobDef::Ptr current_job = job_ptr;
    while(current_job) {
        r_result.push_back(current_job);
        current_job = current_job->next_job_cd_success();
        count++;
        if(count > MAX_CHILDREN_COUNT) {
            throw runtime_error("Too many children exception");
        }
    }
}

/// @brief functions iterates through all jobs using next_job_success and adds all found records to r_result vector
/// @param job_name name of the root job
/// @param r_result vector to which there are added jobs 
void by::JobDefGetter::getChildJobs(const char* job_name, std::vector<by::JobDef::Ptr> &r_result){
    static unsigned count = 0;
    //calling find method to get the job
    by::JobDef::Ptr job_ptr = by::JobDef::find(m_context_ptr, job_name);
    by::JobDef::Ptr current_job = job_ptr;
    while(current_job) {
        r_result.push_back(current_job);
        current_job = current_job->next_job_cd_success();
        count++;
        if(count > MAX_CHILDREN_COUNT) {
            throw runtime_error("Too many children exception");
        }
    }
}