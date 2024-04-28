#pragma once
/// @file db_queries.h
/// @brief class with definitons of queries used in the program
namespace asarum {
namespace BY {

/// @class Queries
/// @brief keeps SQL queries definitions

class Queries {
public:
  /// @brief definition of the query used for getting jobs detail run on Oracle database.
  /// @return text of the query. 
  static const char *getOrclJobDefQuery();
};

} // namespace BY
} // namespace asarum
