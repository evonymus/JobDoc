#pragma once

#include "job.h"
#include <vector>
#include "tokenizer.h"
#include "job_group.h"

namespace asarum {
namespace BY {

/**
 * @file job_proc.h
 * @brief class reading file with jobs definition and generating documentation
 * @class JobProc the class reads jobs definition from the file and generates
 * documenation
 */
class JobProc {
public:
  /**
   * @brief stores the list of fields read from the fist line of the file.
   */
  std::vector<std::string> m_fields_list;

  ///vector stroring groups of jobs executed in a sequence
  std::vector<std::shared_ptr<asarum::BY::JobGroup>> m_job_groups;

  /**
  * The function reads file and puts its content into str string

  * @param fileName - the name of the file to read
  * @param str string to which the file is to be read
  */
  void readFile(const char *fileName, std::string &str);

  /**
   * The function processes the file specified as the parameter:
   * sets m_fields_list and m_jobs fields.
   * @param fieldName the name of the file with definition of the jobs.
   */
  void processFile(const char *fileName);

  /**
  * The function saves SQL, Templates for each Jobs Group 'Jobs' subfolder
  */
  void exportJobs(const std::string &path="./");

  /**
  * @brief the function saves documentation of jobs as a markdown files
  */
  void exportDocs(const std::string &path="./");

private:
  asarum::BY::Tokenizer m_tokenizer;
  void getFieldsDef(const std::string &str);
  void getJobDef(const std::string &str, std::vector<std::string> &vec);
  void addJobs(const std::vector<std::string> &vec);
  void saveFile(const std::string& fileName, const std::string& content);
  bool str_compare(const std::string& a, const std::string& b);
  void printGroupTable(JobGroup& gr, std::ostream& sa );
  void printStepsDescriptions(const JobGroup& gr, std::ostream& sa);
};

} // namespace BY
} // namespace asarum
