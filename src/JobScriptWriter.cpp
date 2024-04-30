#include "asarum/BY/JobScriptWriter.h"
#include <any>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <exception>

namespace by = asarum::BY;
namespace pa = Poco::ActiveRecord;
namespace pd = Poco::Data;
using std::shared_ptr;
using std::type_info;
using fmt=Poco::DateTimeFormatter;

constexpr char *ESC_INSERT = "-- If ESC doesn't exist, create it\n INSERT INTO ENTY_SEL_CTA_T (";
constexpr char *JOB_DEF_INSERT = "-- Insert the parent job definition\n"
                                 "INSERT INTO JOB_DEFN_T (";

constexpr char *SEL_CTA_INSERT = "-- Create mapping JOB->ESC\n"
                                 "INSERT INTO JOB_SEL_CTA_T (JOB_SEL_CTA_ID, OPT_LCK, JOB_CD, ENTY_SEL_CTA_CD)\n";

/// constructor
/// @brief sets
/// @param m_session_ptr
/// @param r_out
asarum::BY::JobScriptWriter::JobScriptWriter(std::ostream &r_out) : mp_out{&r_out}
{
}

void by::JobScriptWriter::writeOrclJobSetScript(const std::vector<asarum::BY::JobDef::Ptr> &r_jobs)
{
}

void by::JobScriptWriter::writeOrclSingleJobScript(const by::JobDef::Ptr job_ptr)
{
    // writeOrclEscScript(job_ptr);
    writeOrclJobScript(job_ptr);
}

//***************************** PRIVATE ***********************

void by::JobScriptWriter::writeOrclEscScript(const by::EntySelCta::Ptr esc_ptr)
{
    (*mp_out) << ESC_INSERT;
    for (const auto i : esc_ptr->columns())
    {
        (*mp_out) << i << ", ";
    }
    (*mp_out) << "SELECT "
              << replaceSingleQuote(esc_ptr->id()) << ","
              << esc_ptr->opt_lck() << ","
              << esc_ptr->enty_sel_cta_desc() << ",";
}

void asarum::BY::JobScriptWriter::writeOrclJobScript(const by::JobDef::Ptr job_ptr)
{
    *mp_out << JOB_DEF_INSERT;
    *mp_out << job_ptr->columns()[0];
    for (int i = 1; i < job_ptr->columns().size(); i++)
    {
        *mp_out << ", " << job_ptr->columns()[i];
    }
    *mp_out << ")\nVALUES ( '" << job_ptr->id() << "'";

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
		sql_cnv(job_ptr->schd_detl_id(), mp_out);
		sql_cnv(job_ptr->prty(), mp_out);
		sql_cnv(job_ptr->actv_yn(), mp_out);
		sql_cnv(job_ptr->next_job_cd_success(), mp_out);
		sql_cnv(job_ptr->next_job_cd_failure(), mp_out);
		sql_cnv(job_ptr->alrt_grp_cd_success(), mp_out);
		sql_cnv(job_ptr->alrt_grp_cd_failure(), mp_out);
		sql_cnv(job_ptr->gen_enty_output_yn(), mp_out);
		sql_cnv(job_ptr->tplt_id(), mp_out);
    *mp_out << ");\n";
}

void asarum::BY::JobScriptWriter::writeOrclSelCtaScript(const by::JobDef::Ptr job_ptr)
{
}

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

void asarum::BY::JobScriptWriter::sql_cnv(const std::any var, std::ostream *p_out) { 
  constexpr char* DTIME_FORMAT="%Y-%m-%d %H:%M:%S";
  constexpr char* DATE_FORMAT="%Y-%m-%d";

  if(auto ptr = std::any_cast<char>(&var)) {
    *p_out << ", '" << *ptr << "'";
  } else if(auto ptr = std::any_cast<std::string>(&var)) {
      *p_out <<  ", '" << *ptr  << "'";
  } else if (auto ptr = std::any_cast<Poco::Int8>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::UInt8>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::Int16>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::UInt16>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::Int32>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::UInt32>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::Int64>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::UInt64>(&var)) {
     *p_out << ", " << *ptr << "";
  } else if (auto ptr = std::any_cast<Poco::DateTime>(&var)) {
    *p_out << ", " << "to_date(" << fmt::format(*ptr, DTIME_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";
  // -----------------  nullable part -----------

  } else if( auto ptr = std::any_cast<Poco::Nullable<std::string>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
         *p_out << ", '" << *ptr << "'";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<char>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", '" << *ptr << "'";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::Int8>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::UInt8>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::Int16>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::UInt16>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::Int32>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::UInt32>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::Int64>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::UInt64>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
        *p_out << ", " << *ptr << "";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::DateTime>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
      *p_out << ", " << "to_date(" << fmt::format(*ptr, DTIME_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";
    }
  } else if( auto ptr = std::any_cast<Poco::Nullable<Poco::DateTime>>(&var)) {
    if(ptr->isNull()) {
         *p_out << ", NULL";
    } else {
      *p_out << ", " << "to_date(" << fmt::format(*ptr, DATE_FORMAT) << ", 'yyyy-mm-dd HH24:mi:ss')";
    }
  } else {
    const std::string msg{"Could not find find SQL conversion for the type: "};
    *mp_out << msg << '\n';
    throw std::invalid_argument(msg);
  } 
}
