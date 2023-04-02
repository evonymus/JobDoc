#pragma once

#include "job.h"
#include "find_str_tfunc.h"
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace by = asarum::BY;

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
}
