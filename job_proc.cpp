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
const char *DOC_DIR = "/Docs";
constexpr unsigned ITEM_LENGTH =
    20; // length of Item column in job steps description
constexpr unsigned VAL_LENGTH =
    40; // length of the value column in jobs definition

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

/// export ESC SQL queries and XML templates to the Jobs folder
/// @param path the path where the Jobs subfoler is to be created
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

// export markdown documentation
void by::JobProc::exportDocs(const std::string &path,
                             const bool withDiagram) {
  const std::string doc_dir = path + DOC_DIR;

  // creating Doc directory

  fs::create_directory(doc_dir);
  for (const auto &gr : m_job_groups) {
    std::ostringstream so;
    printGroupDescription(*gr,so);
    printGroupTable(*gr, so);
    if(withDiagram) {
      printMermaidSequence(*gr, so);
    }
    printStepsDescriptions(*gr, so, withDiagram);
    saveFile(doc_dir + "/" + gr->m_group_name + ".md", so.str());
  }
}

/// @brief the function saves documentation on all job in the single document
/// @param path directory where the document is to be saved
/// @fileName the name of the file in which the document is to be saved
void by::JobProc::exportSingleDoc(const std::string &path,
                                  const std::string &fileName,
                                  const bool withDiagram) {

  const std::string doc_dir = path + DOC_DIR;
  std::ostringstream so;

  // creating Doc directory

  fs::create_directory(doc_dir);
  for (const auto &gr : m_job_groups) {
    printGroupDescription(*gr, so);
    printGroupTable(*gr, so);
    if(withDiagram) {
      printMermaidSequence(*gr, so);
    }
    printStepsDescriptions(*gr, so, withDiagram);
  }

  saveFile(doc_dir + "/" + fileName , so.str());
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

bool by::JobProc::str_compare(const std::string &a, const std::string &b) {
  return a.size() < b.size();
}

/// the function prints out the first sections of the document with job 
/// documentation.
/// @param gr job group for which the section is to be created
/// @os  output stream
void by::JobProc::printGroupDescription(const JobGroup& gr, std::ostringstream& so) {
    so << "# " << gr.m_group_name << "\n\n"
       << "## Description\n\n"
       << gr.m_jobs.at(0)->m_job_descr << "\n\n"
       << "## Components\n\n";
}
/// the function print outs the table with information about the group to
///  the stream given as the parameter
///  @param gr job group for with the table is to be printed out
///  @param sa outpt stream to where the printout is to be made
void by::JobProc::printGroupTable(by::JobGroup &gr, std::ostringstream &sa) {
  //getting max length of the fields printed out in the table
  gr.getMaxFldLen();

  // printing out header of the table
  sa << std::left << "| " << std::setw(gr.m_len_lp) << HEAD_COLS[0] << " | "
     << std::setw(gr.m_len_job_cd) << HEAD_COLS[1] << " | "
     << std::setw(gr.m_len_sub) << HEAD_COLS[3] << " | "
     << std::setw(gr.m_len_next_job) << HEAD_COLS[4] 
    << " |\n";

    // printing out the line below the header
  sa << std::setfill('-') << "| " << std::setw(gr.m_len_lp) << "-"
     << " | " << std::setw(gr.m_len_job_cd) << "-"
     << " | " << std::setw(gr.m_len_sub) << "-"
     << " | " << std::setw(gr.m_len_next_job) << "-"
     << " |\n";
    
    // printing out jobs data
  for (const auto &job : gr.m_jobs) {
    // getting the iterator to the sub-jobs
    auto sj = job->m_sub_jobs_list.begin();

    std::string first_sub_job;
    if(sj != job->m_sub_jobs_list.end()) {
      first_sub_job = *sj;
    } else {
      first_sub_job = " ";
    }

    sa << std::left << std::setfill(' ') << "| " << std::setw(gr.m_len_lp)
       << job->m_step_no << " | " 
      << std::setw(gr.m_len_job_cd) << job->m_job_cd
      << " | " << std::setw(gr.m_len_sub) << first_sub_job 
      << " | " << std::setw(gr.m_len_next_job) << job->m_next_job_success
      << " |\n";


    // if there are sub-jobs present
    if (!job->m_sub_jobs_list.empty()) {
      ++sj; // getting to the next sub-job. The previous one was handled above
      for (; sj != job->m_sub_jobs_list.end(); ++sj) {
        sa << "| " << std::setw(gr.m_len_lp) << " "
           << " | " << std::setw(gr.m_len_job_cd) << " "
           << " | " << std::setw(gr.m_len_sub) << *sj << " | "
           << std::setw(gr.m_len_next_job) << " "
           << " |\n";
      }
    }
  }
  sa << "\n\n";
}

/// the function creates description for for all jobs that are a part of the
/// group
///  @param gr the name of the group of jobs
///  @param sa output string to where the descripiton is to be directed
void by::JobProc::printStepsDescriptions(const JobGroup &gr, std::ostringstream &sa, const bool withDiagram) {
  sa << std::left << "## Steps Description\n\n";
  for (const auto &jb : gr.m_jobs) {
    sa << "## " << jb->m_step_no <<". " << jb->m_job_cd << "\n\n";
    sa << "### Description\n\n";
    sa << jb->m_job_descr << "\n\n";

    sa << "### Definition\n\n";

    sa << std::setfill(' ') << "| " << std::setw(ITEM_LENGTH) << "Item"
       << " | " << std::setw(VAL_LENGTH) << "Value"
       << " |\n";
    sa << "| " << std::setw(ITEM_LENGTH) << std::setfill('-') << "-"
       << " | " << std::setw(VAL_LENGTH) << std::setfill('-') << "-"
       << " |\n";
    sa << std::setfill(' ') << "| " << std::setw(ITEM_LENGTH) << "Job Name"
       << " | " << std::setw(VAL_LENGTH) << jb->m_job_cd << " |\n";
    sa << std::setfill(' ') << "| " << std::setw(ITEM_LENGTH) << "Job Type"
       << " | " << std::setw(VAL_LENGTH) << jb->m_job_type << " |\n";
    // if ESC query exists, add appropriate record
    if (!jb->m_esc.empty()) {
      sa << "| " << std::setw(ITEM_LENGTH) << "ESC Query"
         << " | " << std::setw(VAL_LENGTH) << jb->m_esc << " |\n";
    }

    // if Template in DB exists
    if (!jb->m_templ.empty()) {
      sa << "| " << std::setw(ITEM_LENGTH) << "Database Template"
         << " | " << std::setw(VAL_LENGTH) << jb->m_templ << " |\n";
    }

    // if template specified in a file
    if (!jb->m_tmpl_file.empty()) {
      if(jb->m_tmpl_file.length() < VAL_LENGTH) {
        sa << "| " << std::setw(ITEM_LENGTH) << "Template File"
           << " | " << std::setw(VAL_LENGTH) << std::quoted(jb->m_tmpl_file)
           << " |\n";
      } else {
        sa << "| " << std::setw(ITEM_LENGTH) << "Template File"
           << " | " << std::setw(VAL_LENGTH) << "too long to display"
           << " |\n";
      }
    }
    // if there are sub-jobs present
    if (!jb->m_sub_jobs_list.empty()) {
      auto sb = jb->m_sub_jobs_list.begin();
      sa << std::left << "| " << std::setw(ITEM_LENGTH) << "Sub-Job"
         << " | " << std::setw(VAL_LENGTH) << *sb << " |\n";
      ++sb;
      for (; sb != jb->m_sub_jobs_list.end(); ++sb) {
        sa << "| " << std::setw(ITEM_LENGTH) << ""
           << " | " << std::setw(VAL_LENGTH) << *sb << " |\n";
      }
    }

    sa << "\n\n";

    // if there are sub-jobs and the printout is withDigagram
    // print diagrams for sub-jobs
    if(! jb->m_sub_jobs_list.empty() && withDiagram) {
      printSubjobsDiagram(*jb, sa);
    }
  } // end for group
}

/// The job prints a mermaid flowchart with the sequence of the job in the group
void by::JobProc::printMermaidSequence(const JobGroup& gr, std::ostringstream& so) {

  // if more than one job in the group
  if(gr.m_jobs.size() > 1) {

    so << "### Diagram\n\n";
    so << "```mermaid\ngraph TD\n";
    for(const auto &jb : gr.m_jobs) {
      if(! jb->m_next_job_success.empty()) {
        so << jb->m_job_cd << " -->" << jb->m_next_job_success << "\n";
      }
    }
    so << "```\n\n";
  }
}

/// the function creates diagram showing the list of sub-job called
/// by the job
void by::JobProc::printSubjobsDiagram(const Job& jb, std::ostream& so) {
  if( ! jb.m_sub_jobs_list.empty()) {
    so << "### Diagram\n\n";
    so << "```mermaid\ngraph TD\n";
    auto sj = jb.m_sub_jobs_list.begin();
    so << "A(" << jb.m_job_cd << ") -->" << *sj << '\n';
    ++sj;
    for(; sj != jb.m_sub_jobs_list.end(); ++sj) {
      so << "A -->" << *sj << "\n";
    }
    so << "```\n\n";
  }
}
