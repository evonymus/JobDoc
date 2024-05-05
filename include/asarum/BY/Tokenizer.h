#pragma once
#include <string>
#include <vector>

namespace asarum {
namespace BY {

/**
 * @file tokenizer.h
   @page tokenizer asarum::BY::tokenizer
   @class the class provides methods allowing
   'tokeninzing', i.e. splitting a string into a vector of
   string separated by a tag. The class uses FindStrTFunc class
   @ref FindStrTFunc
*/
class Tokenizer {
public:
  static void tokenize(const std::string &str, const char *sep,
                std::vector<std::string> &vec);
};

} // namespace BY
} // namespace asarum
