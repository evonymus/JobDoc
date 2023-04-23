#ifndef __CON_DEF__
#define __CON_DEF__

#include <string>
#include <soci/soci-backend.h>

namespace asarum {
namespace db {

///abstract class containing definition of getConnString method 
/// returning connection string to a database.
class ConDef {
public:
  virtual const std::string getConString() = 0;
  virtual const soci::backend_factory& getBackendFactory() = 0;

};


} // namespace db
} // namespace asarum


#endif /* ifndef  __CON_DEF__ */
