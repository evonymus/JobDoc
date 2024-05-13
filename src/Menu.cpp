#include "asarum/BY/Menu.h"
#include "asarum/BY/DocWriter.h"
#include "asarum/BY/JobDefGetter.h"
#include "asarum/BY/JobScriptWriter.h"
#include "asarum/BY/SQLiteConnector.h"
#include "asarum/BY/DataCopier.h"
#include "version.h"
#include <boost/filesystem.hpp>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace by = asarum::BY;
namespace fs = boost::filesystem;

constexpr char *JOB_DIR = "\\Jobs";
constexpr char *DOC_DIR = "\\Docs";
constexpr char *SCRIPT_DIR = "\\Scripts";
constexpr char *DEFAULT_DOC_NAME = "JobServerDocument_";
constexpr char *DEFAULT_COPY_DB_NAME = "JobsCopy_";

/// constructor
/// @param argc number of arguments, taken from main
/// @parm *argv[] list of arguments taken from main
by::Menu::Menu(int argc, char *argv[])
    : m_generic_options("Generic Options"), m_source_options("Source of Data"),
      m_output_options("Output Files Options"),
      m_copy_options("Copy Jobs From ODBC to SQLite"),
      m_code_options("Generate Jobs Source Scripts"),
      m_doc_options("Docs Generation"), m_cmd_line_options(),
      m_visible_options("Allowed Options"), m_pos_options()
{

  initMenu(argc, argv);
}

/// @brief function initializes menu
/// @param argc number of arguments, taken from main
/// @parm *argv[] list of arguments taken from main
void by::Menu::initMenu(int argc, char *argv[])
{

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::stringstream ss{};
  // setting the default name of the documentation file
  ss << DEFAULT_DOC_NAME << std::put_time(&tm, "%Y-%m-%d") << ".md";
  m_single_file_name = ss.str();

  ss.str("");
  ss.clear();
  // setting the default name of the file with sqlite copy of the db
  ss << DEFAULT_COPY_DB_NAME << std::put_time(&tm, "%Y-%m-%d") << ".db";
  m_copy_to_db_name = ss.str();
  m_with_images = false;
  // setting default values for variables
  m_path = "./";

  // calling function initializing menu options
  initGenericOptions();
  initSourceOptions();
  initCodeOptions();
  initDocOptions();
  initCopyOptions();
  initOutputOptions();

  m_visible_options.add(m_generic_options)
      .add(m_source_options)
      .add(m_code_options)
      .add(m_doc_options)
      .add(m_copy_options)
      .add(m_output_options);
  m_pos_options.add("file", -1);

  m_cmd_line_options.add(m_generic_options)
      .add(m_source_options)
      .add(m_code_options)
      .add(m_doc_options)
      .add(m_copy_options)
      .add(m_output_options);

  po::store(po::command_line_parser(argc, argv)
                .options(m_cmd_line_options)
                .positional(m_pos_options)
                .run(),
            m_var_map);

}

/// function reacts to input, checks which menu option was selected and
/// calls a funtion tiggering appropriate action
void by::Menu::handleMenu()
{
  po::notify(m_var_map);
  if (m_var_map.empty())
  {
    handleHelp();
  }
  else if (m_var_map.count("version") > 0)
  {
    handleVersion();
  }
  else if (m_var_map.count("help"))
  {
    handleHelp();
    // checking if data source is defined
  }
  else if (m_var_map.count("sqlite") > 0)
  {
    setSQLiteConnector(m_sqlite_name.c_str());
  }
  else if (m_var_map.count("odbc") > 0)
  {
    setOdbcConnector(m_odbc_string.c_str());
  }

  if (m_var_map.count("sequence") + m_var_map.count("all-jobs") > 0)
  {
    handleDocsGeneration();
  }
  else if (m_var_map.count("single") > 0)
  {
    handleSingleJobScriptGeneration();
  }
  else if (m_var_map.count("all") > 0)
  {
    handleScriptAllScheduled();
  }
  else if (m_var_map.count("sequence") + m_var_map.count("all_jobs") > 0)
  {
    std::cout << "\ngenerating documents";
    handleDocsGeneration();
  } else if( m_var_map.count("copy") > 0) {
    handleCopyDB();
  }
}

//------ PRIVATE FUNCTIONS ----------------------------

/***************************************************************/

void by::Menu::initGenericOptions()
{
  m_generic_options.add_options()("version,v", "print version string")(
      "help,h", "print help message");
}

/***************************************************************/

void by::Menu::initSourceOptions()
{
  m_source_options.add_options()(
      "sqlite,l", po::value<std::string>(&m_sqlite_name),
      "file with sqlite db")("odbc,o", po::value<std::string>(&m_odbc_string),
                             "odbc connection string")(
      "schema,t", po::value<std::string>(&m_odbc_schema),
      "schema to connect using ODBC connection");
}

/// initialization of Code  Menu Options

/***************************************************************/

void by::Menu::initCodeOptions()
{
  m_code_options.add_options()("all,a", "Script all scheduled jobs");
}

void by::Menu::initDocOptions()
{
  m_doc_options.add_options()("doc-all-jobs,D", "document all jobs")(
      "doc-seq,d", "document sequence of job triggered by a schedule");
}

/***************************************************************/

void asarum::BY::Menu::initCopyOptions()
{

  m_copy_options.add_options()( "copy,c", "copy from ODBC to SQLite DB");
}


/***************************************************************/

void by::Menu::initOutputOptions()
{
  std::stringstream ss{};
  ss << "(optional) document file name, default " << m_single_file_name;
  const std::string doc_description = ss.str();

  ss.str(""); 
  ss.clear();
  ss << "(optional) name of SQLite copy DB, default " << m_copy_to_db_name;
  const std::string copy_db_description = ss.str();

  m_output_options.add_options()("path,P", po::value<std::string>(&m_path),
                                 "(optional) path to store files")(
      "filename,f", po::value<std::string>(&m_single_file_name),
      doc_description.c_str())(
      "db_file_name,s", po::value<std::string>(&m_copy_to_db_name),
      copy_db_description.c_str()
    ),
      (
      "image,i", "(optional) include sequence diagrams");
}

// ------------- handlers ----------

//**************************************************************

void asarum::BY::Menu::handleSingleJobScriptGeneration()
{
  const std::string script_dir = m_path + SCRIPT_DIR;
  if (m_var_map.count("single") > 0 && m_job_name.length() > 0)
  {
    if (isConnectionDefined())
    {

      std::stringstream ss_file_name;
      ss_file_name << script_dir << "/" << m_job_name << "_src.sql";

      fs::create_directory(script_dir);
      std::ofstream fout(ss_file_name.str());
      by::JobScriptWriter scriptWriter(fout);

      scriptWriter.writeOrclSingleJobScript(m_job_name.c_str(), getSession());
      fout.close();
    }
    else
    {
      throw std::invalid_argument(
          "No data source for script generation defined");
    }
  }
  else
  {
    throw std::invalid_argument("The name of the job was not specified");
  }
}

//**************************************************************

void asarum::BY::Menu::handleCopyDB()
{
  if(m_var_map.count("copy") > 0) {

    // if source ODBC database not specified, throw exception
    if(m_odbc_conn_ptr == nullptr) {
      throw std::invalid_argument("ODBC Source DB not specified");
    }

    std::cout << "\nStarting copying ODBC database ...\n";
    by::DataCopier dataCopier{m_odbc_conn_ptr, m_copy_to_db_name.c_str(), m_odbc_schema.c_str()};
    dataCopier.copyData();
    std::cout << "\nData copied to " << m_copy_to_db_name << " database\n";
  }
}
//**************************************************************
void asarum::BY::Menu::handleScriptAllScheduled()
{
  const std::string script_dir = m_path + SCRIPT_DIR;
  if (m_var_map.count("all") > 0)
  {
    if (isConnectionDefined())
    {
      by::JobDefGetter job_getter{getSession()};
      fs::create_directory(script_dir);

      std::vector<Poco::AutoPtr<asarum::BY::JobDef>> jobs_to_process =
          job_getter.getScheduledJobDefs();
      if (jobs_to_process.size() > 0)
      {
        std::cout << "\nStarting script generation, it may take while ...\n";
      }
      else
      {
        std::cout << "\nNo scheduled job found\n";
      }
      for (auto job : jobs_to_process)
      {
        std::stringstream ss_file_name;
        ss_file_name << script_dir << "/" << job->id() << "_next_src.sql";
        const std::string file_name = ss_file_name.str();

        std::ofstream fout(file_name.c_str());
        by::JobScriptWriter scriptWriter(fout);
        scriptWriter.writeOrclJobSetScript(job->id().c_str(), getSession());
        fout.close();
      }

      std::cout << "\nGeneration of the scripts completed\n";
    }
    else
    {
      throw std::invalid_argument("No data source defined");
    }
  }
  else
  {
    throw std::exception(
        "Incorrectly called handleScriptAllScheduled menu handler");
  }
}
//**************************************************************

void by::Menu::handleDocsGeneration()
{
  const std::string doc_dir = m_path + DOC_DIR;
  fs::create_directory(doc_dir);

  std::stringstream ss{};
  ss << doc_dir << "\\" << m_single_file_name;
  const std::string file_name = ss.str();

  if (!isConnectionDefined())
  {
    throw std::invalid_argument("No connection to database was defined");
  }

  if (m_var_map.count("sequence") + m_var_map.count("all-jobs") > 0)
  {
    by::DocWriter writer{getSession()};
    std::cout
        << "\nGenerating of documentation started, it may take a while ...\n";
    if (m_var_map.count("sequence") > 0)
    {
      writer.docScheduledJobs(file_name);
    }
    else
    {
      writer.docAllJobs(file_name);
    }
    std::cout << "\nGeneration of " << file_name << " document completed\n";
  }
}

/***************************************************************/

void by::Menu::handleHelp()
{
  std::cout
      << "usage jobdoc -f fileName Code|Docs Generation [Output option]  \n\n"
      << m_visible_options << std::endl;
}

void by::Menu::handleVersion()
{
  std::cout << "TMS Job Documenter, version: " << MY_VERSION_MAJOR << "."
            << MY_VERSION_MINOR << std::endl;
}

/**
 * The functions returns true if the file given as the parameter exists
 */
bool by::Menu::fileExists(const char *fileName)
{
  return boost::filesystem::exists(fileName);
}

//***************** Connectors *************************
///
void asarum::BY::Menu::setSQLiteConnector(const char *conn_string)
{
  std::shared_ptr<by::SQLiteConnector> con_ptr{
      new by::SQLiteConnector(m_sqlite_name.c_str())};
  m_sqlite_conn_ptr = std::move(con_ptr);
}

/***************************************************************/

void asarum::BY::Menu::setOdbcConnector(const char *conn_string)
{
  std::shared_ptr<by::OdbcConnector> ptr{new by::OdbcConnector(conn_string)};
  m_odbc_conn_ptr = std::move(ptr);
  if (m_var_map.count("schema") > 0)
  {
    m_odbc_conn_ptr->changeSchema(m_odbc_schema);
  }
}
/***************************************************************/

void asarum::BY::Menu::setDataSource()
{
  if (m_var_map.count("sqlite") > 0)
  {
    setSQLiteConnector(m_sqlite_name.c_str());
  }
}

/***************************************************************/
bool asarum::BY::Menu::isConnectionDefined()
{
  if (m_sqlite_conn_ptr)
  {
    return true;
  }
  else if (m_odbc_conn_ptr)
  {
    return true;
  }
  else
    return false;
}

/***************************************************************/

std::shared_ptr<Poco::Data::Session> asarum::BY::Menu::getSession()
{
  if (m_odbc_conn_ptr != nullptr)
    return m_odbc_conn_ptr->m_session_ptr;
  else if (m_sqlite_conn_ptr != nullptr)
    return m_sqlite_conn_ptr->m_session_ptr;
  else
    throw std::runtime_error("No connection to DB is available");
}
