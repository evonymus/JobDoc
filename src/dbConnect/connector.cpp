#include "connector.h"

namespace db = asarum::db;

/// constructor

db::Connector::Connector(ConDef &conDef)
    : m_sql(conDef.getBackendFactory(), conDef.getConString()) {}

/// the fuction executes sql passed as the parameter
/// @param sql code to execute
void db::Connector::execSql(const std::string &sql) { m_sql << sql; }

/// method returns the result of the query as soci::rowset<soci::row>
/// @param query - the query for which the results is to be returned
soci::rowset<soci::row> db::Connector::getQueryData(const char* query) {
  return (m_sql.prepare << query); }
