#include "test.h"
#include <iostream>
#include "asarum/BY/job_def_getter.h"
#include "asarum/BY/sqlite_connector.h"
#include "asarum/BY/job_def_getter.h"

namespace by=asarum::BY;

void Test::runTest() {
   std::cout << "test run\n"; 
   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::JobDefGetter getter {connector.m_session_ptr};
   auto res = getter.getJobDefs();
   for(const auto i : res) {
    std::cout << i->id() << std::endl;
   }
}