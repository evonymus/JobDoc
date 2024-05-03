#include "asarum/BY/Menu.h"
#include "asarum/BY/job_proc.h"
#include "asarum/BY/SQLiteConnector.h"
#include "asarum/BY/JobScriptWriter.h"
#include "asarum/BY/JobDefGetter.h"
#include "version.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace by = asarum::BY;
namespace fs = boost::filesystem;

constexpr char *JOB_DIR = "/Jobs";
constexpr char *DOC_DIR = "/Docs";
constexpr char *SCRIPT_DIR = "/Scripts";

/// constructor
/// @param argc number of arguments, taken from main
/// @parm *argv[] list of arguments taken from main
by::Menu::Menu(int argc, char *argv[])
    : m_generic_options("Generic Options"), m_source_options("Source of Data"),
      m_db_options("DB Connection"), m_code_options("Code Generation"),
      m_output_options("Output Files Options"),
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
  initGenericOptions();
  initSourceOptions();
  initCodeOptions();
  initDocOptions();
  initOutputOptions();

  m_visible_options.add(m_generic_options)
      .add(m_source_options)
      .add(m_code_options)
      .add(m_doc_options)
      .add(m_output_options);
  m_pos_options.add("file", -1);

  m_cmd_line_options.add(m_generic_options)
      .add(m_source_options)
      .add(m_db_options)
      .add(m_code_options)
      .add(m_doc_options)
      .add(m_output_options);

  po::store(po::command_line_parser(argc, argv)
                .options(m_cmd_line_options)
                .positional(m_pos_options)
                .run(),
            m_var_map);

  // setting default values for variables
  m_path = "./";
  m_single_file_name = "JobServerDocument.md";
  m_with_images = false;
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
  else if (m_var_map.count("sqlite") == 0)
  {
    throw std::invalid_argument("sqlite database needs to be specifies");
  }
  else if (!fileExists(m_sqlite_name.c_str()))
  {
    std::string message_ = "the database " + m_sqlite_name + " does not exist";
    throw std::invalid_argument(message_);
  }
  else if (m_var_map.count("single") > 0)
  {
    handleSingleJobScriptGeneration();
  }
  else if (m_var_map.count("nexts") > 0)
  {
    handleNextJobsScriptsGeneration();
  }
  else if (m_var_map.count("all") > 0)
  {
    handleScriptAllScheduled();
  }
  else if (m_var_map.count("doc") + m_var_map.count("single") > 0)
  {
    handleDocsGeneration();
  }
}

//------ PRIVATE FUNCTIONS ----------------------------

void by::Menu::initGenericOptions()
{
  m_generic_options.add_options()("version,v", "print version string")(
      "help,h", "print help message");
}

void by::Menu::initSourceOptions()
{
  m_source_options.add_options()("sqlite,l",
                                 po::value<std::string>(&m_sqlite_name),
                                 "file with sqlite db");
}

/// initialization of Code  Menu Options
void by::Menu::initCodeOptions()
{
  m_code_options.add_options()("all,a", "Script all scheduled jobs")(
      "single,s", po::value<std::string>(&m_job_name), "generate script for single job and its descendants")(
      "nexts,n", po::value<std::string>(&m_parent_job_name), "generate script for the job and all called on success");
}

void by::Menu::initDocOptions()
{
  m_doc_options.add_options()("one,D", "documentation in a single file")(
      "doc,d", "document per job");
}

void by::Menu::initOutputOptions()
{
  m_output_options.add_options()("path,P", po::value<std::string>(&m_path),
                                 "(optional) path to store files")(
      "output,o", po::value<std::string>(&m_single_file_name),
      "(optional) single documment file name")(
      "image,i", "(optional) include sequence diagrams");
}

// ------------- handlers ----------

//**************************************************************

void asarum::BY::Menu::handleSingleJobScriptGeneration()
{
  const std::string script_dir = m_path + SCRIPT_DIR;
  if (m_var_map.count("single") > 0 && m_job_name.length() > 0)
  {
    if (m_var_map.count("sqlite") > 0)
    {

      std::stringstream ss_file_name;
      ss_file_name << script_dir << "/" << m_job_name << "_src.sql";
      by::SQLiteConnector sqlite_connector{m_sqlite_name.c_str()};
      fs::create_directory(script_dir);
      std::ofstream fout(ss_file_name.str());
      by::JobScriptWriter scriptWriter(fout);
      scriptWriter.writeOrclSingleJobScript(m_job_name.c_str(), sqlite_connector.m_session_ptr);
      fout.close();
    }
    else
    {
      throw std::invalid_argument("No data source defined");
    }
  }
  else
  {
    throw std::invalid_argument("The name of the job was not specified");
  }
}

//**************************************************************

void asarum::BY::Menu::handleNextJobsScriptsGeneration()
{
  const std::string script_dir = m_path + SCRIPT_DIR;

  if (m_var_map.count("nexts") > 0 && m_parent_job_name.length() > 0)
  {
    if (m_var_map.count("sqlite") > 0)
    {
      std::stringstream ss_file_name;
      ss_file_name << script_dir << "/" << m_parent_job_name << "_next_src.sql";
      const std::string file_name = ss_file_name.str();

      by::SQLiteConnector sqlite_connector{m_sqlite_name.c_str()};
      fs::create_directory(script_dir);

      std::ofstream fout(file_name.c_str());
      by::JobScriptWriter scriptWriter(fout);
      scriptWriter.writeOrclJobSetScript(m_parent_job_name.c_str(), sqlite_connector.m_session_ptr);
      fout.close();
    }
    else
    {
      throw std::invalid_argument("No data source defined");
    }
  }
  else
  {
    throw std::invalid_argument("The name of the parent job was not specified");
  }
}

//**************************************************************
void asarum::BY::Menu::handleScriptAllScheduled()
{
  const std::string script_dir = m_path + SCRIPT_DIR;
  if (m_var_map.count("all") > 0)
  {
    if (m_var_map.count("sqlite") > 0)
    {
      by::SQLiteConnector sqlite_connector{m_sqlite_name.c_str()};
      by::JobDefGetter job_getter{sqlite_connector.m_session_ptr};
      fs::create_directory(script_dir);

      std::vector<Poco::AutoPtr<asarum::BY::JobDef>> jobs_to_process = job_getter.getScheduledJobDefs();
      for (auto job : jobs_to_process)
      {
        std::stringstream ss_file_name;
        ss_file_name << script_dir << "/" << job->id() << "_next_src.sql";
        const std::string file_name = ss_file_name.str();

        std::ofstream fout(file_name.c_str());
        by::JobScriptWriter scriptWriter(fout);
        scriptWriter.writeOrclJobSetScript(job->id().c_str(), sqlite_connector.m_session_ptr);
        fout.close();
      }
    }
    else
    {
      throw std::invalid_argument("No data source defined");
    }
  }
  else
  {
    throw std::exception("Incorrectly called handleScriptAllScheduled menu handler");
  }
}
//**************************************************************

void by::Menu::handleDocsGeneration()
{
  by::JobProc jobProc;

  if (m_var_map.count("sqlite") > 0)
  {
    jobProc.getSQLiteData(m_sqlite_name.c_str());
  }
  else
  {
    throw std::invalid_argument("No data source defined");
  }
  if (m_var_map.count("image") > 0)
  {
    m_with_images = true;
  }
  else
  {
    m_with_images = false;
  }
  // if single file option chosen
  if (m_var_map.count("doc"))
  {
    jobProc.exportDocs(m_path, m_with_images);
  }

  // export to a single file
  if (m_var_map.count("one"))
  {
    jobProc.exportSingleDoc(m_path, m_single_file_name, m_with_images);
  }
}

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
