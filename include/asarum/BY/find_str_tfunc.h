#include <algorithm>
#include <string>
namespace asarum {
namespace BY {

/// @file find_str_tfunc.h
/// @brief definition of FindStrTFunc allowing tokenizing using a string and not only a character
/// @class FindStrTFunc 
/// @page FindStrTFunc declaration of FindStrTFunc
class FindStrTFunc {
public:
  FindStrTFunc(const std::string &separator);

  bool operator()(std::string::const_iterator &next,
                  const std::string::const_iterator &end,
                  std::string &tok) const;

  void reset();
  void split();

private:
  std::string m_str;
};

} // namespace BY
} // namespace asarum
