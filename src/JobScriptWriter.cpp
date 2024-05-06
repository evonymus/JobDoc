#include "asarum/BY/JobScriptWriter.h"
#include <any>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <exception>
#include <typeinfo>
#include <sstream>
#include <Poco/ActiveRecord/Query.h>
#include "asarum/BY/JobSelCta.h"
#include "asarum/BY/Tokenizer.h"
#include "asarum/BY/JobDefGetter.h"

namespace by = asarum::BY;
namespace pa = Poco::ActiveRecord;
namespace pd = Poco::Data;
using std::shared_ptr;
using std::type_info;
using fmt = Poco::DateTimeFormatter;

constexpr char *ESC_INSERT = "\n-- If ESC doesn't exist, create it\n INSERT INTO ENTY_SEL_CTA_T (";
constexpr char *JOB_DEF_INSERT = "\n-- Insert the parent job definition\n"
                                 "INSERT INTO JOB_DEFN_T (";

constexpr char *SEL_CTA_INSERT = "\n-- Create mapping JOB->ESC\n"
                                 "INSERT INTO JOB_SEL_CTA_T (JOB_SEL_CTA_ID, OPT_LCK, JOB_CD, ENTY_SEL_CTA_CD)\n";

/// constructor
/// @brief sets
/// @param m_session_ptr
/// @param r_out
asarum::BY::JobScriptWriter::JobScriptWriter(std::ostream &r_out) : mp_out{&r_out}
{
}

//******************************* writeOrclJobSetScript *******************************

void by::JobScriptWriter::writeOrclJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs)
{
  if(r_jobs.size() ==  0 ) {
    throw std::invalid_argument("The passed vector has not jobs");
  }
  *mp_out << "\n-- Start transaction\nBEGIN\n"
          << "\n-- Save point, transaction can be rolled back upon error\nSAVEPOINT start_transaction\n";

  std::vector<asarum::BY::JobDef::Ptr>::const_reverse_iterator ri = r_jobs.rbegin();
  while (ri != r_jobs.rend())
  {
    writeOrclSingleJobScript(*ri);
    ri++;
  }

  *mp_out << "\n-- Commit the transaction\nCOMMIT;\n"
          << "\n-- Handle errors\nEXCEPTION\n-- Rollback transaction"
          << "\n\tWHEN OTHERS THEN"
          << "\n\t\tROLLBACK TO start_transaction;"
          << "\n\t\tRAISE;\n"
          << "\nEND;\n" << std::endl;
}

void asarum::BY::JobScriptWriter::writeOrclJobSetScript(const char *parent_job_name, std::shared_ptr<Poco::Data::Session> session_ptr)
{
  if(session_ptr == nullptr) {
    throw new std::invalid_argument("pointer to the session is null");
  }

  by::JobDefGetter job_getter(session_ptr);

  std::vector<by::JobDef::Ptr> jobs{};
  job_getter.getChildJobs(parent_job_name, jobs);

  if (jobs.size() == 0)
  {
    std::stringstream str{};
    str << "Neither the job: " << parent_job_name << ", nor their childs found";
    throw std::invalid_argument(str.str());
  }
  writeOrclJobSetScript(jobs);
}

//******************************* writeOrclSingleJobScript *******************************

void by::JobScriptWriter::writeOrclSingleJobScript(const by::JobDef::Ptr job_ptr)
{
  constexpr int CHAIN_JOB = 3;
  if (job_ptr == nullptr)
    return;

  *mp_out << "\n/******************  SCRIPT FOR THE JOB: " << job_ptr->id() << " *******************/\n";

  if (job_ptr->job_typ_enu() == CHAIN_JOB)
  {
    *mp_out << "\n------------- creating scripts for chain jobs -----------\n";
    std::vector<std::string> chain_jobs{};
    by::Tokenizer tokenizer{};
    tokenizer.tokenize(job_ptr->parm_1(), ",", chain_jobs);

    for (const auto i : chain_jobs)
    {
      by::JobDef::Ptr ch_job = nullptr;
      ch_job = by::JobDef::find(job_ptr->context(), i);
      if (ch_job != nullptr)
      {
        *mp_out << "\n ----------- creating script for " << ch_job->id() << " chain job ----------\n";
        writeOrclTmplScript(ch_job->tplt_id());
        writeOrclJobScript(ch_job);
      }
    }
  }
  writeOrclJobSelCtaScript(job_ptr);
  writeOrclTmplScript(job_ptr->tplt_id());
  writeOrclJobScript(job_ptr);
}

//******************************* writeOrclSingleJobScript *******************************

void asarum::BY::JobScriptWriter::writeOrclSingleJobScript(const char *job_name,
                                                           std::shared_ptr<pd::Session> session_ptr)
{
  by::JobDefGetter job_getter(session_ptr);

  std::cout << "\n section one\n";

  Poco::AutoPtr<asarum::BY::JobDef> job_ptr = job_getter.getJobDef(job_name);

  std::cout << "\n job is " << job_ptr->id() << "\n";
  if (job_ptr == nullptr)
  {
    std::stringstream str{};
    str << "The job: " << job_name << " not found";
    throw std::invalid_argument(str.str());
  }

  std::cout << "\n calling funtion\n";
  writeOrclSingleJobScript(job_ptr);
}
//***************************** PRIVATE ***********************

/// @brief function writes to the stream specified in the constructor, INSERT statement creating a
/// JOB_DEFN_T record for the job itself and all its next_success and next_failure, jobs.
/// @param job_ptr pointer to the JobDef object, with defintion of the job.
void asarum::BY::JobScriptWriter::writeOrclJobScript(const by::JobDef::Ptr job_ptr)
{
  if (job_ptr == nullptr)
    return;

  *mp_out << JOB_DEF_INSERT;
  *mp_out << job_ptr->columns()[0];
  for (int i = 1; i < job_ptr->columns().size(); i++)
  {
    *mp_out << ", " << job_ptr->columns()[i];
  }
  *mp_out << ")\nSELECT '" << job_ptr->id() << "'";
  sql_cnv(job_ptr->opt_lck(), mp_out);
  sql_cnv(job_ptr->job_desc(), mp_out);
  sql_cnv(job_ptr->schd_typ_enu(), mp_out);
  sql_cnv(job_ptr->job_typ_enu(), mp_out);
  sql_cnv(job_ptr->div_cd(), mp_out);
  sql_cnv(job_ptr->parm_1(), mp_out);
  sql_cnv(job_ptr->parm_2(), mp_out);
  sql_cnv(job_ptr->parm_3(), mp_out);
  sql_cnv(job_ptr->parm_4(), mp_out);
  sql_cnv(job_ptr->parm_5(), mp_out);
  sql_cnv(job_ptr->crtd_dtt(), mp_out);
  sql_cnv(job_ptr->crtd_usr_cd(), mp_out);
  sql_cnv(job_ptr->updt_dtt(), mp_out);
  sql_cnv(job_ptr->updt_usr_cd(), mp_out);
  sql_cnv(job_ptr->tplt_file(), mp_out);
  sql_cnv(job_ptr->outpt_file(), mp_out);

  if (job_ptr->schd_detl_id() != nullptr)
  {
    sql_cnv(job_ptr->schd_detl_id()->id(), mp_out);
  }
  else
  {
    *mp_out << ", NULL";
  }
  sql_cnv(job_ptr->prty(), mp_out);
  sql_cnv(job_ptr->actv_yn(), mp_out);

  if (job_ptr->next_job_cd_success() != nullptr)
  {
    sql_cnv(job_ptr->next_job_cd_success()->id(), mp_out);
  }
  else
  {
    *mp_out << ", NULL";
  }
  if (job_ptr->next_job_cd_failure() != nullptr)
  {
    sql_cnv(job_ptr->next_job_cd_failure()->id(), mp_out);
  }
  else
  {
    *mp_out << ", NULL";
  }
  sql_cnv(job_ptr->alrt_grp_cd_success(), mp_out);
  sql_cnv(job_ptr->alrt_grp_cd_failure(), mp_out);
  sql_cnv(job_ptr->gen_enty_output_yn(), mp_out);
  if (job_ptr->tplt_id() != nullptr)
  {
    sql_cnv(job_ptr->tplt_id()->id(), mp_out);
  }
  else
  {
    *mp_out << ", NULL";
  }
  *mp_out << " FROM DUAL WHERE NOT EXISTS (SELECT 1 FROM JOB_DEFN_T WHERE JOB_CD ='"
          << job_ptr->id() << "');\n\n";
}

/********************************* writeOrclTmplScript **************************************************/

/// @brief saves template into the ADN_T balse
/// @param adtn_ptr record of AdtnData used to create the template
void asarum::BY::JobScriptWriter::writeOrclTmplScript(const asarum::BY::AdtnData::Ptr adt_ptr)
{
  // if template was defined for the job
  if (adt_ptr != nullptr)
  {
    *mp_out << "\n-- if template does not exists, create it\n";
    *mp_out << "INSERT INTO " << adt_ptr->table() << "( ";
    *mp_out << adt_ptr->columns()[0];
    // wrting out the list of columns defined for the table
    for (auto i = 1; i < adt_ptr->columns().size(); i++)
    {
      *mp_out << ", " << adt_ptr->columns()[i];
    }

    *mp_out << ")\nSELECT ADTN_DATA_TSEQ.nextval ";
    sql_cnv(adt_ptr->data(), mp_out);
    sql_cnv(adt_ptr->crtd_dtt(), mp_out);
    sql_cnv(adt_ptr->adtn_data_cd(), mp_out);
    sql_cnv(adt_ptr->adtn_data_typ_enu(), mp_out);
    sql_cnv(adt_ptr->actv_yn(), mp_out);
    sql_cnv(adt_ptr->crtd_usr_cd(), mp_out);
    sql_cnv(adt_ptr->updt_usr_cd(), mp_out);
    sql_cnv(adt_ptr->updt_dtt(), mp_out);
    sql_cnv(adt_ptr->tplt_fmt_typ_enu(), mp_out);

    *mp_out << " FROM DUAL WHERE NOT EXISTS (SELECT 1 FROM ADTN_DATA_T"
            << " WHERE ADTN_DATA_CD = '" << adt_ptr->adtn_data_cd() << "' );\n\n";
  }
}

/********************** writeOrclSelCtaScript *********************/
///@brief the function gets from JOB_SEL_CTA_T proper record for the job given as the parameter
/// and creates a script creating ESC qeury
void asarum::BY::JobScriptWriter::writeOrclJobSelCtaScript(const asarum::BY::JobDef::Ptr job_ptr)
{
  Poco::ActiveRecord::Query<by::JobSelCta> query(job_ptr->context());
  constexpr int OPT_LCK = 1;
  const std::string where = "job_cd ='" + job_ptr->id() + "'";
  const auto result = query
                          .where(where)
                          .execute();

  for (const auto i : result)
  {
    // write ESC query defintion to ENTY_SEL_CTA_T
    writeOrclEscScript(i->enty_sel_cta_cd());

    *mp_out << "\n-------------- creating record in JOB_SEL_CTA_T ---------------\n"
            << "INSERT INTO JOB_SEL_CTA_T (";
    *mp_out << i->columns()[0];
    for (auto j = 1; j < i->columns().size(); j++)
    {
      *mp_out << ", " << i->columns()[j];
    }
    *mp_out << ")\nSELECT " << i->id();
    sql_cnv(i->opt_lck(), mp_out);
    sql_cnv(i->job_cd()->id(), mp_out);
    sql_cnv(i->enty_sel_cta_cd()->id(), mp_out);
    *mp_out << "\nFROM DUAL WHERE NOT EXISTS(SELECT 1 FROM JOB_SEL_CTA_T WHERE JOB_SEL_CTA_ID ="
            << i->id() << ");";
  }
}

/************************** writeOrclEscScript ******************/

void asarum::BY::JobScriptWriter::writeOrclEscScript(const asarum::BY::EntySelCta::Ptr esc_ptr)
{
  *mp_out << "\n-- create ESC Query if it does not exist";
  *mp_out << "\nINSERT INTO ENTY_SEL_CTA_T (";
  // column names are stored in columns() vector;
  *mp_out << esc_ptr->columns()[0];
  for (auto i = 1; i < esc_ptr->columns().size(); i++)
  {
    *mp_out << ", " << esc_ptr->columns()[i];
  }
  *mp_out << ")\nSELECT '" << esc_ptr->id() << "'";
  sql_cnv(esc_ptr->opt_lck(), mp_out);
  sql_cnv(esc_ptr->enty_sel_cta_desc(), mp_out);
  sql_cnv(esc_ptr->div_cd(), mp_out);
  sql_cnv(esc_ptr->str_id_yn(), mp_out);
  sql_cnv(esc_ptr->enty_typ_enu(), mp_out);
  // using wrapper around the SQL code to replace single ' with double ''
  sql_cnv(replaceSingleQuote(esc_ptr->cta_sql()), mp_out);
  sql_cnv(esc_ptr->cta_find_enty(), mp_out);
  sql_cnv(esc_ptr->crtd_dtt(), mp_out);
  sql_cnv(esc_ptr->crtd_usr_cd(), mp_out);
  sql_cnv(esc_ptr->updt_dtt(), mp_out);
  sql_cnv(esc_ptr->updt_usr_cd(), mp_out);
  sql_cnv(esc_ptr->max_entys(), mp_out);
  *mp_out << "\nFROM DUAL WHERE NOT EXISTS(SELECT 1 FROM ENTY_SEL_CTA_T WHERE ENTY_SEL_CTA_CD='"
          << esc_ptr->id() << "');\n";
}

/*************************** replaceSingleQuote    ****************/

/// @brief function replaces single apostroph with two of them
/// @param original original string
/// @return new string with quotes replaced
std::string asarum::BY::JobScriptWriter::replaceSingleQuote(std::string const &original)
{
  std::string results(
      original.size() + std::count(original.begin(), original.end(), '\''),
      '\'');
  std::string::iterator dest = results.begin();
  for (std::string::const_iterator current = original.begin();
       current != original.end();
       ++current)
  {
    if (*current == '\'')
    {
      ++dest;
    }
    *dest = *current;
    ++dest;
  }
  return results;
}

/**************************** sql_cnv ***********************************/

/// @brief function checks type of the variable and adjusts if to be in line with SQL syntax
/// @details ORM mapping allows both nullable and non-nullable variables. For nullable ones, first there is checked
/// if a value is null, if so, then NULL value is returned. There is also checked if a variable is of char or string type
/// and for those ones, the value is endrapped in '<value>' quotation marks.
/// @param var variable of std::any type
/// @param r_out outstream to where there is written the value of the variable
void asarum::BY::JobScriptWriter::sql_cnv(const std::any var, std::ostream *p_out)
{
  constexpr char *DTIME_FORMAT = "%Y-%m-%d %H:%M:%S";
  constexpr char *DATE_FORMAT = "%Y-%m-%d";

  if (auto ptr = std::any_cast<char>(&var))
  {
    *p_out << ", '" << *ptr << "'";
  }
  else if (auto ptr = std::any_cast<std::string>(&var))
  {
    *p_out << ", '" << *ptr << "'";
  }
  else if (auto ptr = std::any_cast<Poco::Int8>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::UInt8>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::Int16>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::UInt16>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::Int32>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::UInt32>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::Int64>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::UInt64>(&var))
  {
    *p_out << ", " << *ptr << "";
  }
  else if (auto ptr = std::any_cast<Poco::DateTime>(&var))
  {
    *p_out << ", "
           << "to_date(" << fmt::format(*ptr, DTIME_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";

    // -----------------  nullable part -----------
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<std::string>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", '" << *ptr << "'";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<char>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", '" << *ptr << "'";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::Int8>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::UInt8>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::Int16>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::UInt16>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<const Poco::Nullable<Poco::Int32>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::UInt32>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::Int64>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::UInt64>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", " << *ptr << "";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::DateTime>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", "
             << "to_date(" << fmt::format(*ptr, DTIME_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";
    }
  }
  else if (auto ptr = std::any_cast<Poco::Nullable<Poco::DateTime>>(&var))
  {
    if (ptr->isNull())
    {
      *p_out << ", NULL";
    }
    else
    {
      *p_out << ", "
             << "to_date(" << fmt::format(*ptr, DATE_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";
    }
  }
  else
  {
    const std::string msg{"Could not find find SQL conversion for the type: "};
    *mp_out << msg << '\n';
    throw std::invalid_argument(msg);
  }
}
