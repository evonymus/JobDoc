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
      /// @brief writes documentation if markdown format for all jobs having a schedule
      /// and all jobs called next using next job on success value.
      /// @param r_file_name - name of the file 
      /// @param with_diagrams  - if set to true, mermaid diagrams are included
      void docScheduledJobs(const std::string &r_file_name,
                            const bool with_diagrams = false);

      /// @brief writes documentation if markdown format for all jobs 
      /// @param r_file_name - name of the file 
      /// @param with_diagrams  - if set to true, mermaid diagrams are included
      void docAllJobs(const std::string &r_file_name,
                      const bool with_diagrams = false);

    private:
      /// @brief stores pointer to JobDefGetter object, getting information about
      // jobs from daatabase
      std::shared_ptr<asarum::BY::JobDefGetter> m_job_getter_ptr;
      std::shared_ptr<std::ostream> m_out_ptr;

      /// @brief print header for the group of the jobs, triggered by a scheduled job
      /// @param job_ptr pointer to the starting (schedduled) job 
      /// @param r_out  pointer to the stream where thre result is sent.
      void printGroupHeader(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);

      /// @brief prints information about schedule of a job 
      /// @param job_ptr pointer to the jobs for which the information is generated 
      /// @param r_out pointer to the output stream 
      void printGroupSchedule(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);

      /// @brief prints mermaid diagram with the sequence of jobs called
      /// @param job_ptr_vec pointer to the vector of jobs for which the diagram is created 
      /// @param r_out output stream 
      void printGroupDiagram(const std::vector<Poco::AutoPtr<JobDef>> job_ptr_vec, std::ofstream &r_out);

      /// @brief prints details about ESC query component
      /// @param esc_ptr - pointer to the EntySelCta object 
      /// @param r_out output stream 
      void printEscDetails(const Poco::AutoPtr<EntySelCta> esc_ptr, std::ofstream &r_out);

      /// @brief prints details about ESC query component
      /// @param job_ptr  pointer to the JobDef object for wich the info about 
      /// ESC query is to be generated. 
      /// @param r_out 
      void printEscDetails(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);

      /// @brief writes details of a job
      /// @param job_ptr pointer to the job 
      /// @param r_out output stream 
      void printJobDetails(const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out);
      void printItemTableDef(std::ofstream &r_out);
      
      /// @brief template used to write a single row in Item / Value table 
      /// @tparam T 
      /// @param value - value to write 
      /// @param label - label for the value  
      /// @param r_out output stream 
      template <typename T> void printItemRow(T value, const char* label, std::ofstream &r_out);

      void printStepsDescriptions(std::vector<Poco::AutoPtr<JobDef>> grp_ptr, std::ofstream &sa, const bool withDiagram);
      
      /// @brief Converts Nullalbe<Poco::Data::Date> to string
      /// @param n_date date to convert 
      /// @return 'Null' or date in the yyyy-mm-dd format
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
