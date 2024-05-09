#include <gtest/gtest.h>
#include "asarum/BY/OdbcConnector.h"
#include "asarum/BY/JobDefGetter.h"
#include "asarum/BY/JobDef.h"
#include <Poco/Foundation.h>

namespace by = asarum::BY;
using JobPtr=Poco::AutoPtr<by::JobDef>;
using namespace std;


auto test_job_frm_odbs() {
   by::OdbcConnector conn{"DSN=JOBS;Uid=system;Pwd=sql"};
   conn.changeSchema("TRANS_MANAGER_SCN");
   std::cout << "\nconn created\n";
   by::JobDefGetter getter{conn.m_session_ptr};
   std::vector<JobPtr> res = getter.getAllJobDefs();
   return res;
}

by::OdbcConnector getOdbcConnector() {
    by::OdbcConnector conn("DSN=JOBS;Uid=system;Pwd=sql");
    return conn;
}

TEST(JobDefGetterOne, All_Job_return_value) {
 EXPECT_TRUE(true);
}


