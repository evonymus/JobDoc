#pragma once

#include "job.h"
#include "job_group.h"
#include "tokenizer.h"
#include <vector>

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

  /// vector stroring groups of jobs executed in a sequence
  /// every job group has a vector of Jobs objects
  std::vector<std::shared_ptr<asarum::BY::JobGroup>> m_job_groups;

  void getData(const char *filename);
  void getSQLiteData(const char *dbName);

  /**
   * Function connects to DB and creates JobGroups
   */
  /*
  void getJobGroupsFromDB(const std::string &service, const std::string &user,
                          const std::string &password);
*/
  /**
   * The function saves SQL, Templates for each Jobs Group 'Jobs' subfolder
   */
  void exportJobs(const std::string &path, const bool withSummary = false);

  /**
   * @brief the function saves documentation of jobs as a markdown files
   */
  void exportDocs(const std::string &path, const bool withDiagram = false);

  void exportSingleDoc(const std::string &path, const std::string &fileName,
                       const bool withDiagram = false);

private:
  asarum::BY::Tokenizer m_tokenizer;
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
   * The function gets data from the given SQLDatabase and creates m_job_groups
   * vector. The vector contains vector with list of jobs
   */
  void processSQLite(const char *dbName);
  void getFieldsDef(const std::string &str);
  void getJobDef(const std::string &str, std::vector<std::string> &vec);
  void addJobs(const std::vector<std::string> &vec);
  void saveFile(const std::string &fileName, const std::string &content);
  bool str_compare(const std::string &a, const std::string &b);

  //**************** Handling Generation of Documents **************************
  void printGroupDescription(const JobGroup &gr, std::ostringstream &so);
  void printGroupTable(JobGroup &gr, std::ostringstream &sa);
  void printStepsDescriptions(const JobGroup &gr, std::ostringstream &sa,
                              const bool withDiagram = false);
  void printMermaidSequence(const JobGroup &gr, std::ostringstream &so);
  void printSubjobsDiagram(const Job &jb, std::ostream &so);
  void printJobSummary(const Job &job, const std::string &fileName);
};

} // namespace BY
} // namespace asarum
