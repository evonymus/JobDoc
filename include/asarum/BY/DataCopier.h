#pragma once
#include <memory>
#include <string>
#include <memory>
#include "OdbcConnector.h"
#include "SQLiteConnector.h"
#include "JobDefGetter.h"
/// @brief imports data from ODBC to SQLite database
namespace asarum
{
    namespace BY
    {
        /// <summary>
        /// The class is used to copy Jobs Definition from ODBC data source to a local
        /// SQLite database
        /// </summary>
        class DataCopier
        {
        public:
            /// @brief constructor
            /// @param odbc_dsn  connection string to ODBC DB
            /// @param db_name  the name of the SQLife DB file name
            /// @param schema   optional, schema name to copy data from 
            DataCopier(const OdbcConnector &odbc_conn_ref, const char* db_name, const char* schema=nullptr );

            /// @brief copies data from m_odbc_dsn ODBC to m_db_name SQLite db
            void copyData();

            virtual ~DataCopier();



        private:
            const char* m_odbc_dsn;
            const char* m_db_name;
            const OdbcConnector m_orig_conn_ref;
            std::unique_ptr<SQLiteConnector> m_dest_conn_ptr;

            /// @brief creates SQLite Database tables
            void createDestDB();

            /// @brief copies templates from ADTN_DATA_T, using from_getter
            /// @param from_getter JobDefGetter object creted using odbc source data 
            /// @param dest_context_ptr Poco::ActiveRecord::Context created for the destination, SQLite database 
            void copyAdtnTemplates(JobDefGetter &from_getter, Poco::ActiveRecord::Context::Ptr dest_context_ptr);
            
            /// @brief copies schedules from SCHD_DETL_T, using from_getter
            /// @param from_getter JobDefGetter object creted using odbc source data 
            /// @param dest_context_ptr Poco::ActiveRecord::Context created for the destination, SQLite database 
            void copySchdlDetls(JobDefGetter &from_getter, Poco::ActiveRecord::Context::Ptr dest_context_ptr);

            /// @brief copies Job Definitions from JOB_DEFN_T, using from_getter
            /// @param from_getter JobDefGetter object creted using odbc source data 
            /// @param dest_context_ptr Poco::ActiveRecord::Context created for the destination, SQLite database 
            void copyJobs(JobDefGetter &from_getter, Poco::ActiveRecord::Context::Ptr dest_context_ptr);

            /// @brief copies Entity Selection Criterias from ENTY_SEL_CTA_T, using from_getter
            /// @param from_getter JobDefGetter object creted using odbc source data 
            /// @param dest_context_ptr Poco::ActiveRecord::Context created for the destination, SQLite database 
            void copyEntySelCtas(JobDefGetter &from_getter, Poco::ActiveRecord::Context::Ptr dest_context_ptr);

            /// @brief copies the content of JOB_SEL_CTA_T table , using from_getter
            /// @param from_getter JobDefGetter object creted using odbc source data 
            /// @param dest_context_ptr Poco::ActiveRecord::Context created for the destination, SQLite database 
            void copyJobSelCtas(JobDefGetter &from_getter, Poco::ActiveRecord::Context::Ptr dest_context_ptr);

        };
    }
}