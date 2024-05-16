#pragma once
///@file include/job_def_getter.h
///@brief class retrieving jobs defintion from a database
#include <Poco/Data/Session.h>
#include <Poco/AutoPtr.h>
#include <Poco/ActiveRecord/Context.h>
#include <memory>
#include <vector>
#include "asarum/BY/JobDef.h"
#include "asarum/BY/JobSelCta.h"
#include "asarum/BY/EntySelCta.h"
namespace asarum {
namespace BY {
using JobPtr=Poco::AutoPtr<JobDef>;
using JobSelCtaPtr=Poco::AutoPtr<JobSelCta>;
using EscMap=std::map<std::string, Poco::AutoPtr<EntySelCta>>;

    class JobDefGetter
    {
    public:
        JobDefGetter (std::shared_ptr<Poco::Data::Session> session_ptr);

        /// @brief gets definition of all jobs as written in JOB_DEFN_T table
        /// @return vector of<JobDef> objects 
        std::vector<Poco::AutoPtr<asarum::BY::JobDef>> getAllJobDefs();

        /// @brief returns pointer to the jobs which name is given as the parameter
        /// @param job_name name of the job 
        /// @return Poco::AutoPtr pointer to the job 
        Poco::AutoPtr<asarum::BY::JobDef> getJobDef(const char* job_name);

        /// @brief function gets data stored in JOB_SEL_CTA_T, table linking 
        /// jobs with EntitySelectionCriteria (ESC)
        /// @return vector of JobSelCta pointers
        /// @param job_ptr, pointer to the job for which selection crtieria is sought
        /// @see asarum::BY::JobSelCta 
        std::vector<JobSelCtaPtr> getJobSelCtas(const JobPtr job_ptr);

        /// @brief gets the content of JOB_DEFN_SEL_CTA_T
        /// @return vector of JobSelCta
        std::vector<Poco::AutoPtr<JobSelCta>> getAllJobSelCtas();

        /// @brief gets those records from ADTN_DATA_T that have ADTN_DATA_CD NOT Null. ADTN_DATA_CD contains the name of the template
        /// @return vector of AdtnData objects 
        std::vector<Poco::AutoPtr<AdtnData>> getAllAdtnTemplates();

        /// @brief gets the content of SCHD_DETL_T table
        /// @return vector of SchdDetl objects 
        std::vector<Poco::AutoPtr<SchdDetl>> getAllSchdDetls();

        std::unique_ptr<EscMap> getEscMap();

        /// @brief function return the content of ENTY_SEL_CTA_T table 
        /// i.e., the table storing ESC queries
        /// @return vector of EntySelCta pointers 
        /// @see asarum::BY:EntySelCta
        std::vector<Poco::AutoPtr<asarum::BY::EntySelCta>> getAllEntySelCtas();

        /// @brief function get the list of the jobs having a schedule. Those ones 
        /// can potentially have NEXT_JOB_CD_SUCCESS set
        /// @return vector of pointers to JobDef 
        std::vector<Poco::AutoPtr<asarum::BY::JobDef>> getScheduledJobDefs();

        ~JobDefGetter ();

        /// @brief The function recurrently gets the jobs indicated by next_job_cd_success
        /// and adds it to the result vector.
        /// @param p_job, pointer to the parent jobs 
        /// @param r_result reference to the vector with pointers of all jobs called in sequence, starting
        // from the parent one, given as the p_job parameter
        void getChildJobs(const asarum::BY::JobDef::Ptr pJob,
                            std::vector<asarum::BY::JobDef::Ptr> &r_result);

        void getChildJobs(const char* job_name,
                            std::vector<asarum::BY::JobDef::Ptr> &r_result);
    private:
        /// @brief session to the datbase
        std::shared_ptr<Poco::Data::Session> m_session_ptr;
        /// @brief context, used to link ActiveRecord with a database
        Poco::ActiveRecord::Context::Ptr m_context_ptr;

    };
}
}