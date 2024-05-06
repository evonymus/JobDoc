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
class JobScriptWriter {
  ///@//d class JobScriptWriter {
public:
  JobScriptWriter(std::ostream &r_out);
  /// @brief writes SQL script with defintion of a single job
  /// @param job_name name of the job
  void writeOrclSingleJobScript(const asarum::BY::JobDef::Ptr job_ptr);
  void writeOrclSingleJobScript(const char* job_name, std::shared_ptr<Poco::Data::Session> session_ptr);

  void writeOrclJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs);
  void writeOrclJobSetScript(const char* parent_job_name, std::shared_ptr<Poco::Data::Session> session_ptr);

private:
  /// @brief stream where script is sent to.
  std::ostream *mp_out;
  void writeOrclEscScript(const asarum::BY::EntySelCta::Ptr esc_ptr);
  void writeOrclJobScript(const asarum::BY::JobDef::Ptr job_ptr);
  void writeOrclJobSelCtaScript(const asarum::BY::JobDef::Ptr job_ptr);
  void writeOrclTmplScript(const asarum::BY::AdtnData::Ptr adt_ptr);

  /// @brief Replaces single apostroph with two of them
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
  void sql_cnv(const std::any var, std::ostream *r_out);
};
} // namespace BY
} // namespace asarum
