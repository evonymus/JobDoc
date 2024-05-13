#include "test.h"
#include <iostream>
#include "asarum/BY/JobDefGetter.h"
#include "asarum/BY/SQLiteConnector.h"
#include "asarum/BY/JobScriptWriter.h"
#include "asarum/BY/EntySelCta.h"
#include "asarum/BY/DataCopier.h"
#include "asarum/BY/DocWriter.h"

namespace by=asarum::BY;

void test_getting_childs() {
   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::JobDefGetter getter {connector.m_session_ptr};
   std::vector<by::JobDef::Ptr> result{};
   getter.getChildJobs("SDL_STR_SEU_UPD_BBUILD", result);
   for(const auto i: result) {
    std::cout << i->id() <<  '\n';

   }

   std::cout << " ------------ REVERSE ---------\n";

   for(std::vector<by::JobDef::Ptr>::reverse_iterator rit = result.rbegin(); rit!=result.rend(); ++rit) {
    std::cout << rit->get()->id() << std::endl;
   }
}

void test_get_columns() {
   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::JobDefGetter getter {connector.m_session_ptr};
  // std::cout << getter.getJobDef("SDL_STR_SEU_UPD_BBUILD")->columns << std::endl;
  std::vector<std::string> vec{getter.getJobDef("SDL_STR_SEU_UPD_BBUILD")->columns()};
  for(auto i : vec) {
   std::cout << i <<std::endl;
  }
}

void test_gen_script() {

   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::JobDefGetter getter {connector.m_session_ptr};
   std::vector<by::JobDef::Ptr> result{};
   getter.getChildJobs("SDL_STR_SEU_UPD_BBUILD", result);
   by::JobScriptWriter writer{std::cout};
   writer.writeOrclJobSetScript(result);

	//Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

}


void test_getting_all_jobs() {
   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::JobDefGetter getter {connector.m_session_ptr};
   auto res = getter.getAllJobDefs();
   for(const auto i : res) {
    std::cout << "Job " << i->id() <<  " Next Job "; 


    if(i->next_job_cd_success()) {
      std::cout << i->next_job_cd_success()->id();
    }
    std::cout << std::endl;
   }
}

void test_job_frm_odbs() {
   by::OdbcConnector conn{"DSN=JOBS;Uid=system;Pwd=sql"};
   conn.changeSchema("TRANS_MANAGER_SCN");
   std::cout << "\nconn created\n";
   by::JobDefGetter getter{conn.m_session_ptr};
   auto res = getter.getAllJobDefs();
   for(const auto i: res) {
      std::cout << i->id() << '\n';
   }
}

void test_CreateDestDB() {
   by::DataCopier copier("DSN=ROE", "MY_DB.db");
   copier.copyData();
}

void test_printDoc() {
   by::SQLiteConnector connector{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
   by::DocWriter writer(connector.m_session_ptr);
   writer.docScheduledJobs("test.md");
}

void test_find_job() {
   by::OdbcConnector conn{"DSN=JOBS;Uid=system;Pwd=sql"};
   conn.changeSchema("TRANS_MANAGER_SCN");
   std::cout << "\nconn created\n";
   by::JobDefGetter getter{conn.m_session_ptr};
   auto ptr = getter.getJobDef("SDL_STR_SEU_UPD_BBUILD");
   if(ptr) {
      std::cout << ptr->id() << '\n';
   } else std::cout << "\n job not found\n";
}

void test_copy_data() {
   by::DataCopier copier("DSN=JOBS;Uid=system;Pwd=sql","my_test.db");
   copier.copyData();
   std::cout << "Data copied\n";
}

void Test::runTest() {
   std::cout << "test run\n"; 
   //test_getting_childs();
  //test_get_columns();
  //test_gen_script();
  //test_CreateDestDB();
  //test_job_frm_odbs();
  //test_printDoc();
  //test_find_job();
  test_copy_data();
}