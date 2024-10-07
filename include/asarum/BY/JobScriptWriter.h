#pragma once
///@file job_script_writer
///@brief class creating SQL scripts, creating jobs for tms
///@author Marek Dziekanski
///@version 0.8
#include "EntySelCta.h"
#include "JobDef.h"
#include <Poco/Data/Session.h>
#include <any>
#include <memory>
#include <ostream>
#include <vector>

namespace asarum {
namespace BY {

/// @brief enumeration used to indicate if the script is to be written for
/// Oracle or MS SQL
enum class DB_VARIANT { ORACLE = 0, MSSQL = 1 };

/// <summary>
/// The class is used to generate SQL script that then can be used to re-create
/// jobs definitions i.e. jobs, templates, ESC queries etc.
/// </summary>
class JobScriptWriter {
  ///@//d class JobScriptWriter {
public:
  JobScriptWriter(std::ostream &r_out);

  void writeSingleJobScript(const asarum::BY::JobDef::Ptr job_ptr,
      DB_VARIANT variant);

  /// @brief generates SQL scripts with defintion of a single job
  /// @param job_name the name of the job
  /// @param session_ptr pointer to the database from where details of the job
  /// @param variant - variant of the DB: Oracle or MSSQL
  /// are taken
  void
  writeSingleJobScript(const char *job_name,
                           std::shared_ptr<Poco::Data::Session> session_ptr,
                           DB_VARIANT variant);




  /// @brief writes script with jobs defintion of a sequence of jobs, using the
  /// vector of jobs given as the parameter
  /// @param r_jobs vector of jobs for which the the scripts are to be created
  /// @param variant either oracle or mssql 
  void
  writeJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs, DB_VARIANT variant);

  /// @brief generates oracle version of scripts for jobs executed sequentially
  /// (using next job on success) the function uses then
  /// writeOraclSingleJobScript to generate scripts for a specific job
  /// @details function uses job name and pointer to the database session to get
  /// the vector of all subsequent jobs, and then call
  /// writeOracleJobSetScript(std::vectir<...>) version of the function
  /// @param parent_job_name name of the jobs starting a job set
  /// @param session_ptr pointer to the session, used to all subsequent job from
  /// a databasse
  void writeOrclJobSetScript(const char *parent_job_name,
                             std::shared_ptr<Poco::Data::Session> session_ptr);

  /// @brief generates oracle version of scripts for jobs executed sequentially
  /// (using next job on success) the function uses then
  /// writeOraclSingleJobScript to generate scripts for a specific job
  /// @param r_jobs vector with pointers to jobs making a set executed together
  void
  writeOrclJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs);

  /// @brief generates mssql version of scripts for jobs executed sequentially
  /// (using next job on success) the function uses then
  /// writeOraclSingleJobScript to generate scripts for a specific job
  /// @details function uses job name and pointer to the database session to get
  /// the vector of all subsequent jobs, and then call
  /// writeOracleJobSetScript(std::vectir<...>) version of the function
  /// @param parent_job_name name of the jobs starting a job set
  /// @param session_ptr pointer to the session, used to all subsequent job from
  /// a databasse
  void writeMssqlJobSetScript(const char *parent_job_name,
                             std::shared_ptr<Poco::Data::Session> session_ptr);

  /// @brief generates mssql version of scripts for jobs executed sequentially
  /// (using next job on success) the function uses then
  /// writeOraclSingleJobScript to generate scripts for a specific job
  /// @param r_jobs vector with pointers to jobs making a set executed together
  void
  writeMssqlJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs);
private:
  /// @brief stream where script is sent to.
  std::ostream *mp_out;
  // begin / commit strings
  void writeOrclTransBegin();
  void writeOrclTransEnd();
  void writeMssqlTransBegin();
  void writeMssqlTransEnd();

  void writeEscScript(const asarum::BY::EntySelCta::Ptr esc_ptr, DB_VARIANT variant);
  void writeJobScript(const asarum::BY::JobDef::Ptr job_ptr, DB_VARIANT variant);
  void writeJobSelCtaScript(const asarum::BY::JobDef::Ptr job_ptr, DB_VARIANT variant);
  void writeTmplScript(const asarum::BY::AdtnData::Ptr adt_ptr, DB_VARIANT variant);
  void writeSchdlDetlScript(const asarum::BY::SchdDetl::Ptr schdl_ptr, DB_VARIANT variant);
  /// @brief gets all subsequent jobs
  /// @param parent paernt job name 
  /// @param session_ptr pointer to session
  /// @return vector pointers to the jobs 
  std::vector<JobDef::Ptr> getSubsequentJobs(const char* parent, std::shared_ptr<Poco::Data::Session> session_ptr);

  /// @brief Replaces single apostroph with two of them.
  /// @param orig_str original string
  /// @return copy of the string with apostophs replaced
  std::string replaceSingleQuote(std::string const &original);

  /// @brief function checks type of the variable and adjusts if to be in line
  /// with SQL syntax
  /// @details ORM mapping allows both nullable and non-nullable variables. For
  /// nullable ones, first there is checked if a value is null, if so, then NULL
  /// value is returned. There is also checked if a variable is of char or
  /// string type and for those ones, the value is endrapped in '<value>'
  /// quotation marks.
  /// @param var variable of std::any type
  /// @param r_out outstream to where there is written the value of the variable
  void sql_cnv_variant(const std::any var, std::ostream *r_out,
                       DB_VARIANT variant);

};
} // namespace BY
} // namespace asarum
