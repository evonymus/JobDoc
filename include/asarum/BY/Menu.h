#pragma once

/**
 * @file menu.h
 * @author Marek Dziekanki 
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <memory>
#include <string>
#include "BaseConnector.h"
#include "SQLiteConnector.h"
#include "OdbcConnector.h"
#include "JobScriptWriter.h"
#include <Poco/Data/Session.h>

namespace po = boost::program_options;
namespace asarum {
namespace BY {
/**
 * @class Menu 
 * @brief configures menu displayed on the screen  
 * 
 */
class Menu {
public:
  /**
   * Constructor
   * @param int argc - number of parameters from command prompt
   * @param argv[] array of argc parameters
   */
  Menu(int argc, char *arv[]);
  /**
   * @brief responses to the options specified in the command prompt and
   * executes appropriate menu handler
   */
  void handleMenu();

  /*************************************************************
   *                  private
   *************************************************************/

private:
  std::shared_ptr<SQLiteConnector> m_sqlite_conn_ptr;
  std::shared_ptr<OdbcConnector> m_odbc_conn_ptr;
  std::string m_notify_list;
  po::options_description m_generic_options;
  po::options_description m_source_options;
  po::options_description m_script_options;
  po::options_description m_code_options;
  po::options_description m_doc_options;
  po::options_description m_output_options;
  po::options_description m_copy_options;

  po::options_description m_visible_options;
  po::options_description m_cmd_line_options;
  po::options_description m_jmeter_options;

  po::positional_options_description m_pos_options;

  po::variables_map m_var_map;

  //-------- variables used by function called
  std::string m_path;
  std::string m_file_name;
  std::string m_config_file_name;
  std::string m_jmeter_file_name;
  std::string m_sqlite_name;
  std::string m_odbc_string;
  std::string m_odbc_schema;
  std::string m_single_file_name;
  // variable used to generate script for a single job
  std::string m_job_name;
  // variable used to generate script for the parent job and all descendants
  std::string m_parent_job_name;
  // name of SQLite database for the copy of ODBC db 
  std::string m_copy_to_db_name;
  DB_VARIANT m_db_variant;
  //--------- db connection
  std::string m_db_service;
  std::string m_db_user;
  std::string m_db_password;


  bool m_with_images;

  void initMenu(int argc, char *argv[]);
  void initGenericOptions();
  void initSourceOptions();
  void initScriptOptions();
  void initCodeOptions();
  void initDocOptions();
  void initCopyOptions();
  void initOutputOptions();

  // ---------- menu handlers (triggers) ---------
  //void handleCodeGeneration(bool withSummary);
  void handleSingleJobScriptGeneration();
  void handleScriptAllScheduled();
  void handleDocsGeneration();
  void handleHelp() const;
  void handleVersion();
  void handleCopyDB();
  void handleCodeOptions();
  void setDataSource();

  // ---------- connection methods -------
  
  /// crates SQLite connector and assigns its address to m_sqllite_conn_ptr
  void setSQLiteConnector(const char* conn_string);
  void setOdbcConnector(const char* conn_string);
  /// @brief checks if there is a connection to database defined
  /// @return true if the connection exists, otherwise false 
  bool isConnectionDefined();
  std::shared_ptr<Poco::Data::Session> getSession();
  /**
   * Returns true if the file given as the parameter exists
   */
  bool fileExists(const char *fileName);
};

} // namespace BY
} // namespace asarum
