#include "asarum/BY/CodeWriter.h"
#include <fstream>

namespace by = asarum::BY;

asarum::BY::CodeWriter::CodeWriter(std::shared_ptr<Poco::Data::Session> session_ptr)
: m_job_getter_ptr{new by::JobDefGetter{session_ptr}} {}

void asarum::BY::CodeWriter::saveEscQueries(const std::string &r_dir)
{
    std::vector<by::EntySelCta::Ptr> selCtas = m_job_getter_ptr->getAllEntySelCtas();

    for (const auto i: selCtas) {
        if (i->cta_sql().isNull() == false) {
			std::stringstream ss {};
			ss << r_dir << "/" << i->id() << ".sql";
			saveSingleQuery(i->cta_sql(), ss.str());
        }
    }
}

void asarum::BY::CodeWriter::saveSingleQuery(const std::string& r_code,
    const std::string &r_file_name)
{
     std::ofstream fout{r_file_name};
  // if stream fails, throw exception
  if (fout.fail())
  {
    std::stringstream msg{};
    msg << "Couldn't open the file " << r_file_name << " for writing";
    throw std::invalid_argument(msg.str());
  }

  fout << r_code;
}