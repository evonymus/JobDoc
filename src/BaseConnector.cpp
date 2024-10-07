#include "asarum/BY/BaseConnector.h"
#include <Poco/Data/Statement.h>

namespace by=asarum::BY;
namespace pd=Poco::Data;

/// <summary>
/// Execute the statement given as the parameter
/// </summary>
/// <param name="sql">SQL code to execute</param>
void asarum::BY::BaseConnector::execSQL(const char * sql)
{
    pd::Statement sql_schema(*m_session_ptr);
    sql_schema << sql, pd::Keywords::now;
    sql_schema.execute();
}