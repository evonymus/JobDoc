#include "job.h"
#include "tokenizer.h"

namespace by = asarum::BY;

/// constructor
///  @param vec reference to the vector that is to be used for initializing
// class fields.
by::Job::Job(const std::vector<std::string> &vec) {
  m_step_no = atoi(vec[STEPS].c_str());
  m_job_cd = vec[JOB_CD];
  m_job_descr = vec[DESCR];
  m_next_job_success = vec[NEXT_JOB];
  m_esc = vec[ESC];
  m_templ = vec[TEMPL];
  m_sql = vec[SQL];
  m_xml = vec[XML];
  m_sub_jobs = vec[SUB_JOBS];
  m_tmpl_file = vec[TMPL_FILE];
  m_subst = vec[SUBST];
  m_api = vec[API];
  m_job_type = vec[TYPE];

  // if m_sub_jobs is not empty, store sub-jobs in m_sug_jobs_list vecto
  if (!m_sub_jobs.empty()) {
    by::Tokenizer tok;
    tok.tokenize(m_sub_jobs, ",", m_sub_jobs_list);
  }
}
