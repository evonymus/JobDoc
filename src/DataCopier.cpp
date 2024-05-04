#include "asarum/BY/DataCopier.h"
#include "asarum/BY/OdbcConnector.h"
#include "asarum/BY/SQLiteConnector.h"
#include "asarum/BY/JobDefGetter.h"
#include "asarum/BY/JobDef.h"
#include "asarum/BY/sql_queries.h"
#include <sstream>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/Data/Transaction.h>
#include <Poco/Data/RecordSet.h>
#include <list>
#include <vector>
namespace by = asarum::BY;
namespace pd = Poco::Data;
using stringstream = std::stringstream;

asarum::BY::DataCopier::DataCopier(const char *odbc_dsn, const char *db_name)
    : m_odbc_dsn{odbc_dsn}, m_db_name{db_name},
      m_orig_conn_ptr{new by::OdbcConnector(odbc_dsn)},
      m_dest_conn_ptr{new by::SQLiteConnector(db_name)}
{
}

void asarum::BY::DataCopier::copyData()
{
    try
    {
        stringstream insert_sql{};
        insert_sql << "INSERT INTO JOB_DEF_T ( ";
        insert_sql << by::JobDef::columns()[0];
        for(auto i = 1; i < by::JobDef::columns().size(); i++) {
           insert_sql << ", "  << by::JobDef::columns()[i];
        }
        
        insert_sql << ") VALUES (?" ;

        for(auto i=1; i < by::JobDef::columns().size(); i++) {
            insert_sql << ", ?";
        }
        insert_sql << ")";


        by::SQLiteConnector frm_conn{"H:\\BY\\JobDoc_TMS_Job_server_documenting_utility\\QA_2024-04-12-10-11-33.db"};
        by::SQLiteConnector to_conn{m_db_name};
        pd::Transaction trans(*to_conn.m_session_ptr);

        //pd::Statement select(*frm_conn.m_session_ptr);
        //select << "SELECT * FROM JOB_DEFN_T", pd::Keywords::into(jobs), pd::Keywords::now;
        //pd::RecordSet rs(*frm_conn.m_session_ptr, "SELECT * from JOB_DEFN_T", new pd::SimpleRowFormatter);
        //pd::Statement insert(*to_conn.m_session_ptr);
        //pd::RecordSet::Iterator it = rs.begin();
        //insert << insert_sql.str(), pd::Keywords::use((*it).names());
        //     insert << pd::Keywords::use(i);
        // }
        //insert << pd::Keywords::now;
        trans.commit();
    }
    catch (const Poco::Exception &ex)
    {
        std::cerr << "Error " << ex.displayText() << std::endl;
    }
}

const char *asarum::BY::DataCopier::getJobSelect()
{
    stringstream select{"SELECT job_cd "};
    for (auto i = 1; i < by::JobDef::columns().size(); i++)
    {
        select << "" << by::JobDef::columns()[i];
    }
    select << " FROM " << by::JobDef::table();
    return select.str().c_str();
}

//**************************************************************

const std::string asarum::BY::DataCopier::getJobInsert()
{
    static stringstream insert;
    if (insert.str().length() == 0)
    {

        insert << "INSERT INTO ";
        insert << by::JobDef::table() << "(" << by::JobDef::columns()[0];
        for (auto i = 1; i < by::JobDef::columns().size(); i++)
        {
            insert << ", " << by::JobDef::columns()[i];
        }
        insert << ") SELECT job_cd ";
        for (auto i = 1; i < by::JobDef::columns().size(); i++)
        {
            insert << "" << by::JobDef::columns()[i];
        }
        insert << " FROM JOB_DEFN_T;";
    }
    return insert.str();
}

//**************************************************************

void asarum::BY::DataCopier::createDestDB()
{
    try
    {
        *m_dest_conn_ptr->m_session_ptr << "DROP TABLE IF EXISTS ENTY_SEL_CTA_T", pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << "DROP TABLE IF EXISTS SCHD_DETL_T", pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << "DROP TABLE IF EXISTS JOB_SEL_CTA_T", pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << "DROP TABLE IF EXISTS JOB_DEFN_T", pd::Keywords::now;

        *m_dest_conn_ptr->m_session_ptr << ENTY_SEL_CTA_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << SCHD_DETL_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << JOB_SEL_CTA_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << JOB_DEFN_T_CREATE, pd::Keywords::now;
    }
    catch (Poco::Exception &ex)
    {
        stringstream msg{"Creating of tables in the database "};
        msg << m_db_name << " failed, Poco:Exception thrown"
            << ex.what() << '\n';
        throw std::exception(msg.str().c_str());
    }
}