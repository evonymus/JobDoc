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
      void printEscDetails(const Poco::AutoPtr<EntySelCta> esc_ptr, std::ofstream &r_out);
      void printEscDetails(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printJobDetails(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printItemTableDef(std::ofstream &r_out);
      template <typename T> void printItemRow(T value, const char* label, std::ofstream &r_out);

      void printStepsDescriptions(std::vector<Poco::AutoPtr<JobDef>> grp_ptr, std::ofstream &sa, const bool withDiagram);
      std::string convertDate(const Poco::Nullable<Poco::Data::Date> &n_date);
      std::string convertDate(const Poco::Data::Date &date);
      /// @brief function converts numeric repestnation of job type to string
      /// @param typ_enu the value of job_typ_enu 
      /// @return scring with description of the type 
      std::string getJobType(int typ_enu);
      /// @brief converts ENTITY_SEL_CTA.ENTY_TYP_ENU into string representation
      /// @param enty_typ_enu numeric code 
      /// @return string representation 
      std::string getEntyTyp(int enty_typ_enu);
      /// @brief Converts SCHD_TYP_ENU to its string representation
      /// @param schd_typ_enu  numeric code
      /// @return string result 
      std::string getSchdTypeEnu(int schd_typ_enu);
    };
  } // namespace BY
} // namespace asarum
