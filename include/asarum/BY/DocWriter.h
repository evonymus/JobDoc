#pragma once
#include <string>
#include <memory>
#include <ostream>
#include <Poco/AutoPtr.h>
#include "JobDefGetter.h"

namespace asarum
{
  namespace BY
  {
    class DocWriter
    {
    public:
      DocWriter(const std::shared_ptr<asarum::BY::JobDefGetter> job_getter_ptr, std::shared_ptr<std::ostream> out_ptr);
      void exportScheduledJobs(const std::string &path, const bool withSummary = false);
      /// @brief the function saves documentation of jobs as a markdown files
      void exportDocs(const std::string &path, const bool withDiagram = false);

      void exportSingleDoc(const std::string &path, const std::string &fileName,
                           const bool withDiagram = false);

    private:
      std::shared_ptr<asarum::BY::JobDefGetter> m_job_getter_ptr;
      std::shared_ptr<std::ostream> m_out_ptr;
    };
  } // namespace BY
} // namespace asarum
