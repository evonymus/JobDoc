#include "asarum/BY/DocWriter.h"
#include "asarum/BY/JobDef.h"
#include "asarum/BY/Tokenizer.h"
#include <Poco/Data/Date.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <fstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>

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
    msg << "Couldn't open the file " << r_file_name << " for writing";
    throw std::invalid_argument(msg.str());
  }
  std::vector<Poco::AutoPtr<asarum::BY::JobDef>> schdl_jobs =
      m_job_getter_ptr->getScheduledJobDefs();
  for (const auto i : schdl_jobs)
  {
    printGroupHeader(i, fout);
    printGroupSchedule(i, fout);

    std::vector<Poco::AutoPtr<asarum::BY::JobDef>> jobs{};
    m_job_getter_ptr->getChildJobs(i, jobs);

    printStepsDescriptions(jobs, fout, false);
    fout << "\n\n## Details of Job Components\n\n";
    for (const auto j : jobs)
    {
      printEscDetails(j, fout);
      printJobDetails(j, fout);
    }
  }
}

/***************************************************************/

void asarum::BY::DocWriter::docAllJobs(const std::string &r_file_name,
                                       const bool with_diagrams)
{
  std::ofstream fout{r_file_name};
  // if stream fails, throw exception
  if (fout.fail())
  {
    std::stringstream msg{};
    msg << "Couldn't open the file " << r_file_name << " for writing";
    throw std::invalid_argument(msg.str());
  }
  std::vector<Poco::AutoPtr<by::JobDef>> all_jobs = m_job_getter_ptr->getAllJobDefs();
  
  // if not jobs found, write message and leave the program
  if(all_jobs.empty()) {
    std::cout << "\n There is no job to document found\n";
    return;
  }
  fout << "\n\n# List of all jobs \n\n";
  
  for(const auto i : all_jobs) {
      printEscDetails(i, fout);
      printJobDetails(i, fout);
  }
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

      printItemTableDef(r_out);

      r_out << std::setfill(' ') << "| " << std::setw(NAME_LENGTH) << "Recurrence"
            << " | " << std::setw(VALUE_LENGTH);

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
        printItemRow(job_ptr->schd_detl_id()->itvl(), "Interval", r_out);
      }
      printItemRow(convertDate(job_ptr->schd_detl_id()->efct_dt()),
                   "EffectiveDate", r_out);
      printItemRow(convertDate(job_ptr->schd_detl_id()->expd_dt()),
                   "ExpirationDate", r_out);
      if (!job_ptr->schd_detl_id()->day_of_mth().isNull())
      {
        printItemRow(job_ptr->schd_detl_id()->day_of_mth().value(),
                     "Day Of Month", r_out);
      }
    }
  }

  /***************************************************************/

  void by::DocWriter::printStepsDescriptions(
      std::vector<Poco::AutoPtr<by::JobDef>> grp_ptr, std::ofstream & r_out,
      const bool withDiagram)
  {
    const int n_no = 4;
    const int n_job_cd = 40;
    const int n_job_type = 30;

    int counter = 0;

    r_out << "\n## Job Set Components\n";

    r_out << "\n|" << std::setw(n_no) << "No"
          << " | " << std::setw(n_job_cd)
          << "Job Name"
          << " | " << std::setw(n_job_type) << "Type"
          << "|\n"
          << "|" << std::setw(n_no) << std::setfill('-') << '-' << " | "
          << std::setw(n_job_cd) << std::setfill('-') << '-' << " | "
          << std::setw(n_job_type) << std::setfill('-') << '-' << "|\n"
          << std::setfill(' ');

    for (const auto i : grp_ptr)
    {
      r_out << "|" << std::setw(n_no) << ++counter << " | " << std::setw(n_job_cd)
            << i->id() << " | " << std::setw(n_job_type)
            << getJobType(i->job_typ_enu()) << "|\n";
    }
  }

  /***************************************************************/

  void asarum::BY::DocWriter::printEscDetails(
      const Poco::AutoPtr<by::JobDef> job_ptr, std::ofstream &r_out)
  {
    const auto jb_sel_cta = m_job_getter_ptr->getJobSelCtas(job_ptr);
    for (const auto i : jb_sel_cta)
    {
      printEscDetails(i->enty_sel_cta_cd(), r_out);
    }
  }
  /***************************************************************/
  void asarum::BY::DocWriter::printEscDetails(
      const Poco::AutoPtr<EntySelCta> esc_ptr, std::ofstream &r_out)
  {
    if (esc_ptr == nullptr)
      return;
    r_out << "\n### ESC Query\n\n";
    // write ESC description
    if (!esc_ptr->enty_sel_cta_desc().isNull())
    {
      r_out << "\n**Description**: " << esc_ptr->enty_sel_cta_desc().value()
            << "\n\n";
    }
    printItemTableDef(r_out);
    printItemRow(esc_ptr->id(), "ESC Name", r_out);
    // DIV_CD if exists
    if (!esc_ptr->div_cd().isNull())
    {
      printItemRow(esc_ptr->div_cd().value(), "Division", r_out);
    }
    printItemRow(getEntyTyp(esc_ptr->enty_typ_enu()), "Entity Type", r_out);
    printItemRow(esc_ptr->crtd_usr_cd(), "Created By", r_out);
    printItemRow(convertDate(esc_ptr->crtd_dtt()), "Created On", r_out);

    if (!esc_ptr->updt_dtt().isNull())
    {
      printItemRow(convertDate(esc_ptr->updt_dtt().value()), "Updated On", r_out);
    }

    if (!esc_ptr->updt_usr_cd().isNull())
    {
      printItemRow(esc_ptr->crtd_usr_cd(), "Updated By", r_out);
    }

    if (!esc_ptr->max_entys().isNull())
    {
      printItemRow(esc_ptr->max_entys().value(), "Max Entities", r_out);
    }
  }

  /***************************************************************/
  void asarum::BY::DocWriter::printJobDetails(const Poco::AutoPtr<JobDef> job_ptr,
                                              std::ofstream &r_out)
  {
    std::vector<std::string> chain_job_names{};
    std::vector<Poco::AutoPtr<by::JobDef>> chain_jobs{};
    const int API = 2;
    const int CHAIN = 3;

    r_out << "\n\n### Details of " << job_ptr->id() << "\n\n";
    if (!job_ptr->job_desc().isNull())
    {
      r_out << "**Description**: " << job_ptr->job_desc() << "\n\n";
    }
    printItemTableDef(r_out);
    printItemRow(job_ptr->id(), "Job Name", r_out);
    printItemRow(getSchdTypeEnu(job_ptr->schd_typ_enu()), "Sched. Type", r_out);
    printItemRow(getJobType(job_ptr->job_typ_enu()), "Job Type", r_out);

    // if job is API, write API name
    if (job_ptr->job_typ_enu() == API && job_ptr->parm_1().isNull() == false)
    {
      printItemRow(job_ptr->parm_1().value(), "API called", r_out);
    }
    // if job type is Chain and chain jobs are defined
    if (job_ptr->job_typ_enu() == CHAIN && job_ptr->parm_1().isNull() == false)
    {
      by::Tokenizer::tokenize(job_ptr->parm_1().value(), ",", chain_job_names);
      printItemRow(chain_job_names[0], "Chain Jobs", r_out);
      // vector to store definition of the chain jobs
      for (auto i = 1; i < chain_job_names.size(); i++)
      {
        printItemRow(chain_job_names[i], "", r_out);
        chain_jobs.push_back(
            m_job_getter_ptr->getJobDef(chain_job_names[i].c_str()));
      }
    }
    printItemRow(job_ptr->actv_yn(), "Active", r_out);
    printItemRow(convertDate(job_ptr->crtd_dtt()), "Created On", r_out);
    printItemRow(job_ptr->crtd_usr_cd(), "Created By", r_out);

    // if job was updated
    if (!job_ptr->updt_dtt().isNull())
    {
      printItemRow(convertDate(job_ptr->updt_dtt().value()), "Updated On", r_out);
    }
    // updated by
    if (!job_ptr->updt_usr_cd().isNull())
    {
      printItemRow(job_ptr->updt_usr_cd().value(), "Updated By", r_out);
    }

    // if template is stored in a file
    if (!job_ptr->tplt_file().isNull())
    {
      std::string value = job_ptr->tplt_file().value();
      std::replace(value.begin(), value.end(), '\\', '/');
      int strSize = value.size();
      // if string > max cell size, trim it to the size
      printItemRow(strSize > VALUE_LENGTH ? value.substr(strSize - VAL_LENGTH)
                                          : value,
                   "Template File", r_out);
    }

    if (!job_ptr->next_job_cd_success().isNull())
    {
      printItemRow(job_ptr->next_job_cd_success()->id().c_str(),
                   "Next on Success", r_out);
    }

    if (!job_ptr->next_job_cd_failure().isNull())
    {
      printItemRow(job_ptr->next_job_cd_failure()->id().c_str(),
                   "Next on Failure", r_out);
    }

    // printing template names
    if (!job_ptr->tplt_id().isNull() || chain_jobs.size() > 0)
    {
      r_out << "\n\n### Templates\n\n";
      printItemTableDef(r_out);
      if (!job_ptr->tplt_id().isNull())
      {
        // printing JobName, Template Name
        printItemRow(job_ptr->tplt_id()->adtn_data_cd().value(),
                     job_ptr->id().c_str(), r_out);
      }
      for (const auto i : chain_jobs)
      {
        if (!i->tplt_id().isNull())
        {
          // printing JobName, Template Name
          printItemRow(i->tplt_id()->adtn_data_cd().value(), i->id().c_str(),
                       r_out);
        }
      }
    }
  }

  /***************************************************************/

  std::string asarum::BY::DocWriter::convertDate(
      const Poco::Nullable<Poco::Data::Date> &n_date)
  {
    if (n_date.isNull())
      return "Null";
    else
    {
      std::stringstream ss{};
      ss << n_date.value().year() << "-" << std::setfill('0') << std::setw(2)
         << n_date.value().month() << "-" << std::setfill('0') << std::setw(2)
         << n_date.value().day();
      return ss.str();
    }
  }

  /***************************************************************/

  std::string asarum::BY::DocWriter::convertDate(const Poco::Data::Date &date)
  {
    std::stringstream ss{};
    ss << date.year() << "-" << std::setfill('0') << std::setw(2) << date.month()
       << "-" << std::setfill('0') << std::setw(2) << date.day();
    return ss.str();
    return std::string();
  }
  /***************************************************************/

  std::string asarum::BY::DocWriter::getJobType(int typ_enu)
  {
    switch (typ_enu)
    {
    case 1:
      return "RRS";
      break;
    case 2:
      return "Api";
      break;
    case 3:
      return "Chain";
      break;
    case 4:
      return "Decision";
      break;
    case 6:
      return "MMSI";
      break;
    case 7:
      return "TV_OCEAN_TRUCK";
      break;
    case 8:
      return "Intra OS Import";
      break;
    case 17:
      return "Intra Booking Send";
      break;
    case 18:
      return "Intra Booking Rec.";
      break;
    case 19:
      return "Directory Watch";
      break;
    case 20:
      return "Transp. Ord. Consolid.";
      break;
    case 22:
      return "Dispatch";
      break;
    case 23:
      return "Tracking";
      break;
    case 25:
      return "Reoptimization";
      break;
    case 26:
      return "Notification";
      break;
    default:
      return "Unknown";
    }
    return std::string();
  }

  /***************************************************************/
  void asarum::BY::DocWriter::printItemTableDef(std::ofstream & r_out)
  {
    r_out << std::left << std::setfill(' ') << "| " << std::setw(NAME_LENGTH)
          << "Item"
          << " | " << std::setw(VALUE_LENGTH) << "Value"
          << " |\n";
    r_out << "| " << std::setw(NAME_LENGTH) << std::setfill('-') << "-"
          << " | "
          << std::setw(VALUE_LENGTH) << std::setfill('-') << "-"
          << " |\n";
  }

  /***************************************************************/
  template <typename T>
  void asarum::BY::DocWriter::printItemRow(T item, const char *label,
                                           std::ofstream &r_out)
  {
    r_out << std::left << std::setfill(' ') << "| " << std::setw(NAME_LENGTH)
          << label << " | " << std::setw(VALUE_LENGTH) << item << " |"
          << std::endl;
  }

  /***************************************************************/

  std::string asarum::BY::DocWriter::getEntyTyp(int enty_typ_enu)
  {
    switch (enty_typ_enu)
    {
    case 1:
      return "Shipment";
      break;
    case 2:
      return "Shipment Leg";
      break;
    case 3:
      return "Load";
      break;
    case 4:
      return "Stop";
      break;
    case 5:
      return "Container";
      break;
    case 6:
      return "Item";
      break;
    case 7:
      return "Trip";
      break;
    case 8:
      return "Load At";
      break;
    case 9:
      return "Consignee";
      break;
    case 10:
      return "Hub";
      break;
    case 11:
      return "Distr. Center";
      break;
    case 12:
      return "Plan";
      break;
    case 13:
      return "Appointment";
      break;
    case 14:
      return "Manifest";
      break;
    case 15:
      return "Tariff";
      break;
    default:
      return "Other";
    }
  }

  /***************************************************************/

  std::string asarum::BY::DocWriter::getSchdTypeEnu(int schd_typ_enu)
  {
    switch (schd_typ_enu)
    {
    case 1:
      return "On Demand";
      break;
    case 2:
      return "Scheduled";
      break;
    case 3:
      return "Startup";
      break;
    default:
      return "Other";
    }
  }
