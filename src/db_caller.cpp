#include "db_caller.h"
#include "db_queries.h"
#include <string>
#include <vector>
#include <soci/soci.h>
#include <iostream>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

namespace by=asarum::BY;
// namespace db=asarum::db;

by::DbCaller::DbCaller(db::OrclConDef& conDef) : m_connector(conDef) {}


/// function calls JOB_DEFS query and fills in job_group vector
void by::DbCaller::getJobGroups(std::vector<std::shared_ptr<asarum::BY::JobGroup>>& job_groups) {
  soci::rowset<soci::row> rows = m_connector.getQueryData(by::Queries::getOrclJobDefQuery());
  std::shared_ptr<by::JobGroup> pGroup_ = nullptr;

  // soci uses indicators to indicate if a column is or is not NULL. If a colummn returns a 
  // non null value, the function get_indicator(col_num) returns soci::i_ok
  soci::indicator ind_;

  // iterating through the returned rowset
  for(auto& row: rows) {
    // the first field containt the group name. Create a group for the field
    ind_ = row.get_indicator(0); 
    // if the first columnt is not null
    if( ind_ == soci::i_ok)  {
      // creating a new group
      std::shared_ptr<by::JobGroup> new_group {new by::JobGroup(row.get<std::string>(0))};

      // pointer to the group
      pGroup_ = new_group;
      // adding the job group to the vector with all job groups
      job_groups.push_back(new_group);
    }

    // iterating through the list of columns and adding their values to the fields vector
    std::vector<std::string> fields_;

    for(auto i = 0; i < row.size(); i++) {
      
      // getting indicator showing whether a column is not null
      ind_ = row.get_indicator(i);

      // if the column is not null
      if( ind_ == soci::i_ok) {
        // column nr 2, 1 counting from zero, is a numeric value
        if(i==1) fields_.push_back(std::to_string(row.get<double>(i)));
        else     fields_.push_back(row.get<std::string>(i));

      // if column is NULL, put empty string or "0", depending on type
      } else {
        if(i==1) fields_.push_back("0");
        else fields_.push_back("");
      }
    }

    // create the job using the fields_ vector
    std::shared_ptr<by::Job> job{new by::Job(fields_)} ;
    // add the job to the group
    pGroup_->addJob(job);
    // creating a new Job object using fields vector
    // adding the job to the group
  }
}

//---------------------- private -----------------

template <typename T> T by::DbCaller::getFieldValue(const T& value) {
   return value; 
}
