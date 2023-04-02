#include "find_str_tfunc.h"
#include <algorithm>
#include <string>

using namespace asarum::BY;

FindStrTFunc::FindStrTFunc(const std::string &separator) : m_str(separator) {}

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
