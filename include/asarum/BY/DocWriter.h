#pragma once
#include <string>
#include <memory>
#include <ostream>
#include <Poco/AutoPtr.h>
#include "JobDefGetter.h"

namespace asarum
{
  namespace BY
  {
    class DocWriter
    {
    public:
      DocWriter(const std::shared_ptr<Poco::Data::Session> session_ptr);
      void docScheduledJobs(const std::string &r_file_name,
                            const bool with_diagrams = false);
      /// @brief the function saves documentation of jobs as a markdown files

      void docAllJobs(const std::string &r_file_name,
                      const bool with_diagrams = false);

    private:
      std::shared_ptr<asarum::BY::JobDefGetter> m_job_getter_ptr;
      std::shared_ptr<std::ostream> m_out_ptr;
      void printGroupHeader(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printGroupSchedule(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printGroupComponents(const std::vector<Poco::AutoPtr<JobDef>> job_ptr_vec, std::ofstream &r_out);
      void printGroupDiagram(const std::vector<Poco::AutoPtr<JobDef>> job_ptr_vec, std::ofstream &r_out);
      void printJobHeader(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printJobDetais(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);

      void printStepsDescriptions(std::vector<Poco::AutoPtr<JobDef>> grp_ptr, std::ofstream &sa, const bool withDiagram);
      std::string convertNullDate(const Poco::Nullable<Poco::Data::Date> &n_date);
      /// @brief function converts numeric repestnation of job type to string
      /// @param typ_enu the value of job_typ_enu 
      /// @return scring with description of the type 
      std::string getJobType(int typ_enu);
    };
  } // namespace BY
} // namespace asarum
