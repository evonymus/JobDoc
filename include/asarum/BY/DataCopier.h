#pragma once
#include <memory>
#include <string>
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
            DataCopier(const char* odbc_dsn, const char* db_name );
            void copyData();
            void createDestDB();

       // private:
            const char* m_odbc_dsn;
            const char* m_db_name;
            std::unique_ptr<OdbcConnector> m_orig_conn_ptr;
            std::unique_ptr<SQLiteConnector> m_dest_conn_ptr;
            const char* getJobSelect();
            static const std::string getJobInsert();
            const char* getEntySelCtaSelect();
            const char* getEntySelCtaInsert();
        };
    }
}