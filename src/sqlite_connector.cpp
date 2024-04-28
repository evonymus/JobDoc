#include "asarum/BY/sqlite_connector.h"
#include "asarum/BY/job.h"
#include "asarum/BY/job_group.h"
#include "asarum/BY/sql_queries.h"
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <iostream>
#include <memory>
#include <string>

namespace by = asarum::BY;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;

by::SQLiteConnector::SQLiteConnector(const char *dbName) {
  try {
    init();
    std::shared_ptr<Session> session_{new Session("SQLite", dbName)};
    m_session_ptr = session_;
  } catch (Poco::Exception &ex) {
    std::cout << "Could not connect to the database " << dbName
              << ", reason: " << ex.displayText() << std::endl;
    throw ex;
  }
}
//*************************************************************
void by::SQLiteConnector::getJobs(
    std::vector<std::shared_ptr<JobGroup>> &job_groups) {
  std::string fld[FIELDS_NO];
  unsigned level = 0;
  Statement select(*m_session_ptr);
  std::shared_ptr<by::JobGroup> current_group = nullptr;

  select << JOB_DEFS, into(fld[0]), into(fld[1]), into(fld[2]), into(fld[3]),
      into(fld[4]), into(fld[5]), into(fld[6]), into(fld[7]), into(fld[8]),
      into(fld[9]), into(fld[10]), into(fld[11]), into(fld[12]), into(fld[13]),
      range(0, 1);

  // get one record at time
  while (!select.done()) {
    select.execute();
    level = atoi(fld[1].c_str());
    // if master job, create JobGroup
    if (level == 1) {
      std::shared_ptr<by::JobGroup> group_{new by::JobGroup(fld[0])};
      current_group = group_;
      job_groups.push_back(group_);
    }
    std::vector<std::string> jb_flds(std::begin(fld), std::end(fld));
    std::shared_ptr<by::Job> job{new by::Job(jb_flds)};
    current_group->addJob(job);
  }
}

//************************ PRIVATE *****************************

void by::SQLiteConnector::init() { SQLite::Connector::registerConnector(); }

void by::SQLiteConnector::shutDown() {
  SQLite::Connector::unregisterConnector();
}
