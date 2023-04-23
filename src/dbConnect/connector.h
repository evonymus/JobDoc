#ifndef __CONNECTOR__
#define __CONNECTOR__

#include "con-def.h"
#include <soci/session.h>
#include <soci/soci.h>
#include <vector>
#include <memory>

namespace asarum {
namespace db {

constexpr unsigned ROWS_RETURNED = 300;

class Connector {
public:
  /// constructor
  /// @param conDef, const reference to a ConDef object storing
  /// details of the connection.
  Connector(ConDef &conDef);

  void execSql(const std::string &sql);
  // template for returning query result

  ///metod returning data as a rowset or rows
  soci::rowset<soci::row> getQueryData(const char* query);
  soci::session m_sql;
};
} // namespace db
} // namespace asarum
#endif /* ifndef __CONNECTOR__ */
