#ifndef __ORCL_CONN_DEF__
#define __ORCL_CONN_DEF__
#include "con-def.h"
#include <soci/oracle/soci-oracle.h>

namespace asarum {
namespace db {

/// Oracle implementation of abstract class ConnDef
class OrclConDef : public ConDef {
public:
  OrclConDef(const std::string service, const std::string user,
             const std::string password);

  virtual const std::string getConString();
  virtual const soci::backend_factory& getBackendFactory();

  std::string m_service;
  std::string m_user;
  std::string m_password;
};

} // namespace db
} // namespace asarum
#endif /* ifndef __ORCL_CONN_DEF__ */
