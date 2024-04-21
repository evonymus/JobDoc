#pragma once

#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace asarum {
namespace BY {

const int FIELDS_NO = 14; // number of fields in the vector
///
/// enumeratin storing fields names in the sequence returned by the query taking
/// data from a DB
enum field {
  MASTER,
  STEPS,
  JOB_CD,
  NEXT_JOB,
  SUB_JOBS,
  ESC,
  TEMPL,
  SQL,
  XML,
  SUBST,
  TMPL_FILE,
  DESCR,
  API,
  TYPE
};

class Job {
public:
  Job();
  Job(const std::vector<std::string> &vec);

  unsigned m_step_no;
  std::string m_job_cd;
  std::string m_next_job_success;
  std::string m_sub_jobs;
  std::string m_esc;
  std::string m_templ;
  std::string m_sql;
  std::string m_xml;
  std::string m_subst;
  std::string m_tmpl_file;
  std::string m_job_descr;
  std::string m_api;
  std::string m_job_type;

  std::vector<std::string> m_sub_jobs_list;
};

} // namespace BY
} // namespace asarum
