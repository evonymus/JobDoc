#include "test.h"
#include <iostream>
#include "asarum/BY/job_def_getter.h"
#include "asarum/BY/sqlite_connector.h"
#include "asarum/BY/job_def_getter.h"
#include "asarum/BY/JobScriptWriter.h"

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
   by::JobScriptWriter writer{std::cout};
  // std::cout << getter.getJobDef("SDL_STR_SEU_UPD_BBUILD")->columns << std::endl;
  writer.writeOrclSingleJobScript(getter.getJobDef("SDL_STR_SEU_UPD_BBUILD"));

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

void Test::runTest() {
   std::cout << "test run\n"; 
   //test_getting_childs();
  //test_get_columns();
  test_gen_script();
}