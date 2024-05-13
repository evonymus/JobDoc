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
namespace pa = Poco::ActiveRecord;
using stringstream = std::stringstream;
using JobPtr_t = Poco::AutoPtr<by::JobDef>;

asarum::BY::DataCopier::DataCopier(const char *odbc_dsn, const char *db_name, const char *schema)
    : m_odbc_dsn{odbc_dsn}, m_db_name{db_name},
      m_orig_conn_ptr{new by::OdbcConnector(odbc_dsn)},
      m_dest_conn_ptr{new by::SQLiteConnector(db_name)}

{
    // if schema parameter specified, change schema
    if (schema != nullptr)
    {
        m_orig_conn_ptr->changeSchema(schema);
    }
}

/***************************************************************/

asarum::BY::DataCopier::DataCopier(std::shared_ptr<OdbcConnector> odbc_conn_ptr, const char *db_name, const char *schema)
    : m_odbc_dsn{nullptr}, m_db_name{db_name},
      m_orig_conn_ptr{odbc_conn_ptr},
      m_dest_conn_ptr{new by::SQLiteConnector(db_name)}
{
    // if schema parameter specified, change schema
    if (schema != nullptr)
    {
        m_orig_conn_ptr->changeSchema(schema);
    }
}
/***************************************************************/

void asarum::BY::DataCopier::copyData()
{
    try
    {
        by::JobDefGetter from_getter{m_orig_conn_ptr->m_session_ptr};
        pa::Context::Ptr dest_context_ptr{new pa::Context(*m_dest_conn_ptr->m_session_ptr)};

        std::vector<JobPtr_t> jobs = from_getter.getAllJobDefs();

        // if no record found, throw exceptin
        if (jobs.empty())
        {
            std::stringstream ss{};
            ss << "No job defintion found in the source database " << m_db_name;
            throw std::invalid_argument(ss.str());
        }
        createDestDB();

        // copying JOB_DEFN_T and ADTN_DATA_T
        for (const auto i : jobs)
        {
            // if template record exists, create a template record
            if (!i->tplt_id().isNull())
            {
                by::AdtnData::Ptr tmpl_ptr = new by::AdtnData(*i->tplt_id());
                tmpl_ptr->create(dest_context_ptr);
            }
            by::JobDef::Ptr job_ptr = new by::JobDef(*i);
            job_ptr->create(dest_context_ptr);
        }

        std::vector<JobSelCtaPtr> job_esc_ptr = from_getter.getAllSelCtas();

        // if not ESC fond, throw exception
        if (job_esc_ptr.empty())
        {
            std::stringstream ss{};
            ss << "No ESC queries found in the source databaee " << m_db_name;
            throw std::invalid_argument(ss.str());
        }

        for (const auto i : job_esc_ptr)
        {
            // inserting ESC query
            by::EntySelCta::Ptr esc_ptr = new by::EntySelCta(*i->enty_sel_cta_cd());
            esc_ptr->create(dest_context_ptr);

            by::JobSelCta::Ptr jb_cta_ptr = new by::JobSelCta(*i);
            jb_cta_ptr->create(dest_context_ptr);
        }
    }
    catch (const Poco::Exception &ex)
    {
        std::cerr << "Error " << ex.displayText() << std::endl;
    }
}

/// @brief descturctor. Closing connections
asarum::BY::DataCopier::~DataCopier()
{
    if (m_dest_conn_ptr->m_session_ptr != nullptr)
    {
        m_dest_conn_ptr->m_session_ptr->close();
    }

    if (m_orig_conn_ptr->m_session_ptr != nullptr)
    {
        m_orig_conn_ptr->m_session_ptr->close();
    }
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
        *m_dest_conn_ptr->m_session_ptr << "DROP TABLE IF EXISTS ADTN_DATA_T", pd::Keywords::now;

        *m_dest_conn_ptr->m_session_ptr << ENTY_SEL_CTA_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << SCHD_DETL_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << JOB_SEL_CTA_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << JOB_DEFN_T_CREATE, pd::Keywords::now;
        *m_dest_conn_ptr->m_session_ptr << ADTN_DATA_T_CREATE, pd::Keywords::now;
    }
    catch (Poco::Exception &ex)
    {
        stringstream msg{"Creating of tables in the database "};
        msg << m_db_name << " failed, Poco:Exception thrown"
            << ex.what() << '\n';
        throw std::exception(msg.str().c_str());
    }
}