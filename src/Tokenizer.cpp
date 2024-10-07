#include "asarum/BY/Tokenizer.h"
#include "asarum/BY/FindStrTFunc.h"
#include <boost/tokenizer.hpp>

namespace by = asarum::BY;

/**
* @brief the function splits the provided string using the separator
* or 'token' and puting the result into the res vector
* @param str the string to split
* @param token the separator to use
* @param res the vector with splitied strings
* 
* the function uses FindStrTFunc 
* @ref FindStrTFunc
*/
void by::Tokenizer::tokenize(const std::string& str, const char* token
                           , std::vector<std::string>& res) {
  typedef boost::tokenizer<by::FindStrTFunc> tok_t;
  by::FindStrTFunc sep(token);

  tok_t fields(str,sep);
  for(const auto &fld : fields) {
    res.push_back(fld);
  }
}
