#include "asarum/BY/DocWriter.h"
#include "asarum/BY/JobDef.h"
#include <boost/filesystem/operations.hpp>
#include <utility>
#include <vector>

namespace pc = Poco;
namespace fs = boost::filesystem;
namespace by = asarum::BY;

using Job_ptr_t = pc::AutoPtr<by::JobDef>;
using Vec_jb_ptr_t = std::vector<Job_ptr_t>;
using Job_grp_t = std::vector<std::pair<Job_ptr_t, Vec_jb_ptr_t>>;

constexpr char *JOB_DIR = "/Jobs";
constexpr char *DOC_DIR = "/Doc";


// length of Item column in job steps description
constexpr unsigned ITEM_LENGTH = 20;
// length of the value column in jobs definition
constexpr unsigned VAL_LENGTH = 40;
asarum::BY::DocWriter::DocWriter(const std::shared_ptr<asarum::BY::JobDefGetter> job_getter_ptr, std::shared_ptr<std::ostream> out_ptr)
{
  m_job_getter_ptr = job_getter_ptr;
  m_out_ptr = out_ptr;
}
void asarum::BY::DocWriter::exportScheduledJobs(const std::string &path,
                                                const bool withSummary) {
  const std::string job_path = path + JOB_DIR;
  // vector with the pair<parent_job_ptr,  
  Job_grp_t jb_grp{};
  // getting the list of scheduled jobs
  std::vector<pc::AutoPtr<asarum::BY::JobDef>> schd_job_ptr{
      m_job_getter_ptr->getScheduledJobDefs()};
  for (const auto i : schd_job_ptr) {
    const auto child_jobs = m_job_getter_ptr->getScheduledJobDefs();
    jb_grp.push_back(std::make_pair(i, child_jobs));
  }
}

void asarum::BY::DocWriter::exportDocs(const std::string &path,
                                       const bool withDiagram) {}

void asarum::BY::DocWriter::exportSingleDoc(const std::string &path,
                                            const std::string &fileName,
                                            const bool withDiagram) {}
