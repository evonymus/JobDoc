#include "asarum/BY/FindStrTFunc.h"
#include <algorithm>
#include <string>

using namespace asarum::BY;

///constructor
/// @param separator the separator to be used for tokenizing 
FindStrTFunc::FindStrTFunc(const std::string &separator) : m_str(separator) {}

/// overloaded operator () used for checking if iterator for the tokenized 
/// reached the end of the string
/// @param next iterator showing next character
/// @param end iterator showing the end of the string
/// @return false if reaching the end of the string
bool FindStrTFunc::operator()(std::string::const_iterator &next,
                              const std::string::const_iterator &end,
                              std::string &tok) const {
  if (next == end) {
    return false;
  }
  const std::string::const_iterator foundToken =
      std::search(next, end, m_str.begin(), m_str.end());

  tok.assign(next, foundToken);
  next = (foundToken == end) ? end : foundToken + m_str.size();
  return true;
}

void FindStrTFunc::reset() {}
