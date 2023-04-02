#include "job_proc.h"
#include <boost/filesystem/operations.hpp>
#include <boost/tokenizer.hpp>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace by = asarum::BY;
namespace fs = std::filesystem;

const unsigned BUFF_SIZE = 4096;
// token separating jobs definitions
const char *JB_TOKEN = "{EOL}";
// token separating job fields
const char *FLD_TOKEN = "{R}";
const char *JOB_DIR = "/Jobs";
const char* DOC_DIR = "/Docs";

void by::JobProc::readFile(const char *fileName, std::string &str) {
  std::ifstream myFile;
  myFile.open(fileName);
  char buffer[BUFF_SIZE];

  if (myFile.is_open()) {
    while (myFile.read(buffer, sizeof(buffer))) {
      str.append(buffer, sizeof(buffer));
    }
  } else {
    std::string error_{"Couldn't open the file: "};
    error_ += fileName;
    throw std::invalid_argument(error_);
  }
}

/**
 * The function reads the file, tokenizes it, and creates JobGroups
 * and adds to them appropriate jobs
 */
void by::JobProc::processFile(const char *fileName) {
  std::string str;
  std::vector<std::string> jobs_;

  readFile(fileName, str);
  // splits the string into the jobs_ vector
  m_tokenizer.tokenize(str, JB_TOKEN, jobs_);

  // if there is any job definition present
  if (jobs_.size() > 0) {
    getFieldsDef(jobs_[0]);
  }
  std::shared_ptr<by::JobGroup> jb_grp_ptr_ = nullptr;

  for (auto i = 1; i < jobs_.size(); i++) {
    std::vector<std::string> fields;
    getJobDef(jobs_[i], fields);

    // if the first field is not empty i.e., a new job group begins
    if (fields[0].empty() == false) {
      std::shared_ptr<by::JobGroup> new_group_{new by::JobGroup(fields[0])};
      jb_grp_ptr_ = new_group_;
      m_job_groups.push_back(new_group_);
    }
    if (jb_grp_ptr_ != nullptr) {
      std::shared_ptr<by::Job> job_def_{new by::Job(fields)};
      jb_grp_ptr_->addJob(job_def_);
    }
  }
}

/// export ESC SQL queries and XML templates
void by::JobProc::exportJobs(const std::string &path) {
  const std::string job_dir = path + JOB_DIR;

  // creating directory
  fs::create_directory(job_dir);

  for (const auto &gr : m_job_groups) {
    std::string grp_dir = job_dir + "/" + gr->m_group_name;
    fs::create_directory(grp_dir);

    for (const auto &jb : gr->m_jobs) {
      // used ostream to format the file name
      std::ostringstream so;
      so << std::setfill('0') << std::setw(3) << jb->m_step_no << "_"
         << jb->m_job_cd;
      const std::string file_patrn = grp_dir + "/" + so.str();

      saveFile(file_patrn + ".xml", jb->m_xml);
      saveFile(file_patrn + ".sql", jb->m_sql);
    }
  }
}

//export markdown documentation
void by::JobProc::exportDocs(const std::string &path) {
  const std::string doc_dir = path + DOC_DIR;

  // creating Doc directory
  fs::create_directory(doc_dir);
  for(const auto &gr : m_job_groups) {
    std::ostringstream so;
    so << "# " << gr->m_group_name << "\n\n"
       << "## Description\n\n"
       << gr->m_jobs.at(0)->m_job_descr << "\n\n"
       << "## Components\n\n";

  }
}



// ====================== PRIVATE FUNCTIONS ===========

void by::JobProc::getFieldsDef(const std::string &str) {
  m_tokenizer.tokenize(str, FLD_TOKEN, m_fields_list);
}

/**
 * The function splits str string with a job definition into individual
 * fiels and puts them in th vec vector
 * @param str string to split
 * @param vec vector in where there are stored the fields
 */
void by::JobProc::getJobDef(const std::string &str,
                            std::vector<std::string> &vec) {
  m_tokenizer.tokenize(str, FLD_TOKEN, vec);
}

void by::JobProc::addJobs(const std::vector<std::string> &vec) {
  std::shared_ptr<std::vector<std::string>> job_{
      new std::vector<std::string>()};

  // field 1 contains
  m_tokenizer.tokenize(vec.at(1), FLD_TOKEN, *job_);
}

void by::JobProc::saveFile(const std::string &fileName,
                           const std::string &content) {
  std::ofstream fout(fileName);
  fout << content;
  fout.flush();
  fout.close();
}

bool by::JobProc::str_compare(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}
