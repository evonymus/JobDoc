#pragma once
#include <memory>
#include <string>
#include <memory>
#include "OdbcConnector.h"
#include "SQLiteConnector.h"
/// @brief imports data from ODBC to SQLite database
namespace asarum
{
    namespace BY
    {
        class DataCopier
        {
        public:
            /// @brief constructor
            /// @param odbc_dsn  connection string to ODBC DB
            /// @param db_name  the name of the SQLife DB file name
            /// @param schema   optional, schema name to copy data from 
            DataCopier(const char* odbc_dsn, const char* db_name, const char* schema=nullptr );
            DataCopier(std::shared_ptr<OdbcConnector> odbc_conn_ptr, const char* db_name, const char* schema=nullptr );

            /// @brief copies data from m_odbc_dsn ODBC to m_db_name SQLite db
            void copyData();

            virtual ~DataCopier();


        private:
            const char* m_odbc_dsn;
            const char* m_db_name;
            std::shared_ptr<OdbcConnector> m_orig_conn_ptr;
            std::unique_ptr<SQLiteConnector> m_dest_conn_ptr;

            /// @brief creates SQLite Database tables
            void createDestDB();

        };
    }
}