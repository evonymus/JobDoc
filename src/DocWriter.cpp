#include "asarum/BY/DocWriter.h"
#include "asarum/BY/JobDef.h"
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Data/Date.h>
#include <iomanip>
#include <utility>
#include <vector>
#include <fstream>

namespace pc = Poco;
namespace pd = Poco::Data;
namespace by = asarum::BY;

constexpr char *JOB_DIR = "/Jobs";
constexpr char *DOC_DIR = "/Doc";
constexpr int NAME_LENGTH = 30;
constexpr int VALUE_LENGTH = 50;

// length of Item column in job steps description
constexpr unsigned ITEM_LENGTH = 20;
// length of the value column in jobs definition
constexpr unsigned VAL_LENGTH = 40;

asarum::BY::DocWriter::DocWriter(
    const std::shared_ptr<Poco::Data::Session> session_ptr)
    : m_job_getter_ptr{new by::JobDefGetter{session_ptr}} {}

/***************************************************************/

void asarum::BY::DocWriter::docScheduledJobs(const std::string &r_file_name,
                                             const bool withSummary)
{
  std::ofstream fout{r_file_name};
  // if stream fails, throw exception
  if (fout.fail())
  {
    std::stringstream msg{};
    msg << "Couldn't opne the file " << r_file_name << " for writing";
    throw std::invalid_argument(msg.str());
  }
  std::vector<Poco::AutoPtr<asarum::BY::JobDef>> schdl_jobs = m_job_getter_ptr->getScheduledJobDefs();
  for (const auto i : schdl_jobs)
  {
    printGroupHeader(i, fout);
    printGroupSchedule(i, fout);

    std::vector<Poco::AutoPtr<asarum::BY::JobDef>> jobs{}; 
    m_job_getter_ptr->getChildJobs(i, jobs);

    printStepsDescriptions(jobs, fout, false);
  }
  fout.close();
}

/***************************************************************/

void asarum::BY::DocWriter::docAllJobs(const std::string &r_file_name,
                                       const bool with_diagrams)
{
}

//******************************** PRIVATE *******************************

void asarum::BY::DocWriter::printGroupHeader(
    const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out)
{
  r_out << "\n# " << job_ptr->id() << '\n'
        << "\n## Description" << '\n'
        << '\n'
        << job_ptr->job_desc() << '\n';
}

//**************************************************************
void asarum::BY::DocWriter::printGroupSchedule(
    const Poco::AutoPtr<JobDef> job_ptr, std::ofstream &r_out)
{
  if (job_ptr->schd_detl_id() != nullptr)
  {
    r_out << "\n## Schedule Details\n\n";
    r_out << std::setfill(' ') << "| " << std::setw(NAME_LENGTH) << "Item"
          << " | "
          << std::setw(VALUE_LENGTH) << "Value"
          << " |\n";
    r_out << "| " << std::setw(NAME_LENGTH) << std::setfill('-') << "-"
          << " | "
          << std::setw(VALUE_LENGTH) << std::setfill('-') << "-"
          << " |\n";

    r_out << std::setfill(' ') << "| " << std::setw(NAME_LENGTH) << "Recurrence"
          << " | "
          << std::setw(VALUE_LENGTH);

    switch (job_ptr->schd_detl_id()->rcurnce_typ_enu())
    {
    case 1:
      r_out << "Daily";
      break;
    case 2:
      r_out << "Montlly";
      break;
    case 3:
      r_out << "Fixed Interval";
      break;
    default:
      r_out << "Other";
    }

    r_out << " |\n";
    // if interval is set, print its deatils
    if (job_ptr->schd_detl_id()->itvl() > 0)
    {
      r_out << "| " << std::setw(NAME_LENGTH) << "Interval"
            << " | " << std::setw(VALUE_LENGTH) << job_ptr->schd_detl_id()->itvl() << " |\n";
    }
    r_out << "| " << std::setw(NAME_LENGTH) << "Effective Date"
          << " | " << std::setw(VALUE_LENGTH)
          << convertNullDate(job_ptr->schd_detl_id()->efct_dt())
          << " |\n"
          << "| " << std::setw(NAME_LENGTH) << "Expiration Date"
          << " | " << std::setw(VALUE_LENGTH)
          << convertNullDate(job_ptr->schd_detl_id()->expd_dt())
          << " |\n";

    if (!job_ptr->schd_detl_id()->day_of_mth().isNull())
    {
      r_out << "| " << std::setw(NAME_LENGTH) << "Day Of Month"
            << " | " << std::setw(VALUE_LENGTH)
            << job_ptr->schd_detl_id()->day_of_mth().value()
            << " |\n";
    }
  }
}

void by::DocWriter::printStepsDescriptions(std::vector<Poco::AutoPtr<by::JobDef>> grp_ptr,
                                           std::ofstream &r_out,
                                           const bool withDiagram)
{
  const int n_no = 4;
  const int n_job_cd = 30;
  const int n_job_type = 20;
  const int n_sub_jobs = 25;

  int counter = 0;

  r_out << "\n## Job Set Components\n";

  r_out << "\n|" << std::setw(n_no) << "No" 
  << " | " << std::setw(n_job_cd) << "Job Name"
  << " | " << std::setw(n_job_type) << "Type"
  << " | " << std::setw(n_sub_jobs) << "Sub Jobs" 
  << "|\n"
  << "|"   << std::setw(n_no)     << std::setfill('-') << '-'  
  << " | " << std::setw(n_job_cd) << std::setfill('-') << '-'
  << " | " << std::setw(n_job_type) << std::setfill('-') << '-' 
  << " | " << std::setw(n_sub_jobs) <<std::setfill('-') << '-' << "|\n" 
  << std::setfill(' ');

  for(const auto i: grp_ptr) {
    r_out << "|" << std::setw(n_no) << ++counter 
  << " | " << std::setw(n_job_cd) << i->id() 
  << " | " << std::setw(n_job_type) << getJobType(i->job_typ_enu()) 
  << " | " << std::setw(n_sub_jobs) << "Sub Jobs" 
  << "|\n";
  }
}

std::string asarum::BY::DocWriter::convertNullDate(const Poco::Nullable<Poco::Data::Date> &n_date)
{
  if (n_date.isNull())
    return "Null";
  else
  {
    std::stringstream ss{};
    ss << n_date.value().year() << "-"
       << std::setfill('0') << std::setw(2) << n_date.value().month() << "-"
       << std::setfill('0') << std::setw(2) << n_date.value().day();
    return ss.str();
  }
}

std::string asarum::BY::DocWriter::getJobType(int typ_enu)
{
  switch(typ_enu) {
    case 1: return "RRS"; break;
    case 2: return "Api"; break;
    case 3: return "Chain"; break;
    case 4: return "Decision"; break;
    case 6: return "MMSI"; break;
    case 7: return "TV_OCEAN_TRUCK"; break;
    case 8: return "Intra OS Import"; break;
    case 17: return "Intra Booking Send";break;
    case 18: return "Intra Booking Rec."; break;
    case 19: return "Directory Watch"; break;
    case 20: return "Transp. Ord. Consolid."; break;
    case 22: return "Dispatch"; break;
    case 23: return "Tracking"; break;
    case 25: return "Reoptimization"; break;
    case 26: return "Notification"; break;
    default: return "Unknown";
  }
return std::string();
}