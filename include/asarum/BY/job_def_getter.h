#pragma once
///@file include/job_def_getter.h
///@brief class retrieving jobs defintion from a database
#include <Poco/Data/Session.h>
#include <Poco/AutoPtr.h>
#include <memory>
#include <vector>
#include "asarum/BY/JobDef.h"
#include "asarum/BY/JobSelCta.h"
#include "asarum/BY/EntySelCta.h"
namespace asarum {
namespace BY {
    class JobDefGetter

    {
    public:
        JobDefGetter (std::shared_ptr<Poco::Data::Session> session_ptr);
        /// @brief gets definition of jobs as written in JOB_DEFN_T table
        /// @return vector of<JobDef> objects 
        std::vector<Poco::AutoPtr<asarum::BY::JobDef>> getJobDefs();
        std::vector<Poco::AutoPtr<asarum::BY::JobSelCta>> getJobSelCtas();
        std::vector<Poco::AutoPtr<asarum::BY::EntySelCta>> getEntySelCtas();

        ~JobDefGetter ();
    private:
        std::shared_ptr<Poco::Data::Session> m_session_ptr;

    };

}
}