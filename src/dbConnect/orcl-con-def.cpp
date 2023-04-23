#include "orcl-con-def.h"

#include <soci/oracle/soci-oracle.h>

namespace db = asarum::db;

const soci::backend_factory& oracle_factory = *soci::factory_oracle();


/// constructor
/// @param service the name of the service from tnsnames.ora
/// @user user id
/// @password password
db::OrclConDef::OrclConDef(const std::string service, const std::string user,
                           const std::string password)
    : m_service(service), m_user(user), m_password(password) {
}

/// the method returns connection string used to connect to an oracle DB
const std::string db::OrclConDef::getConString() {
  return "service=" + m_service + " user=" + m_user +
         " password=" + m_password;
}

/// returns reference to oracle_backend_factory
 const soci::backend_factory& db::OrclConDef::getBackendFactory() {
  return oracle_factory;
}


