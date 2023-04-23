#ifndef _DB_CALLER
#define _DB_CALLER
#include <string>
#include <memory>
#include "job_group.h"
#include "dbConnect/orcl-con-def.h"
#include "dbConnect/connector.h"


namespace asarum {
namespace BY {

///class used to take data from DB 
class DbCaller {
public:

  /// constructor
  /// @param conDef reference to ConDef object storing DB connection 
  /// details
  DbCaller(asarum::db::OrclConDef& conDef);

  void getJobGroups(std::vector<std::shared_ptr<asarum::BY::JobGroup>>& job_groups);

private:
    asarum::db::Connector m_connector;
    template <typename T> T getFieldValue(const  T& value);
  /* data */
};
} // namespace BY
} // namespace asarum
#endif /* ifndef _DB_CALLER  */
