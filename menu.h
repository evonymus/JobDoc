#pragma once
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <string>

namespace po = boost::program_options;
namespace asarum {
namespace BY {
/**
 * Class contains menu options displayed by the program
 *
 * **/
class Menu {
public:
  /**
   * Constructor
   * @param int argc - number of parameters from command prompt
   * @param argv[] array of argc parameters
   */
  Menu( int argc,  char *arv[]);
  /**
   * @brief responses to the options specified in the command prompt and
   * executes appropriate menu handler
   */
  void handleMenu();

private:
  std::string m_notify_list;
  po::options_description m_generic_options;
  po::options_description m_source_options;
  po::options_description m_code_options;
  po::options_description m_doc_options;
  po::options_description m_output_options;

  po::options_description m_visible_options;
  po::options_description m_cmd_line_options;

  po::positional_options_description m_pos_options;

  po::variables_map m_var_map;

  //-------- variables used by function called
  std::string m_path;
  std::string m_file_name;
  std::string m_single_file_name;
  bool m_with_images;

  void initMenu( int argc,  char *argv[]);
  void initGenericOptions();
  void initSourceOptions();
  void initCodeOptions();
  void initDocOptions();
  void initOutputOptions();

  // ---------- menu handlers (triggers) ---------
  void handleCodeGeneration(bool withSummary);
  void handleDocsGeneration();
  void handleHelp();
  void handleVersion();
  /*
            po::options_description m_config_options;
            po::options_description m_analyses_options;
            po::options_description m_cmd_line_options;
            po::options_description m_visible_options;
            po::options_description m_db_options;

            po::variables_map m_var_map;
            po::positional_options_description m_pos_options;


            void setGenericOptions();
            void setConfigOptions();
            void setAnalysesOptions();
            void setDBOptions();

            void handleOutput();
            void handleHelp();
            void handleVersion();
            void handleUpdate();
            void handleNotify();
            void handleBase();
            void handleCurrentRates();
            void handleSpecificCurrency();
            void handleCurrencyFromTo();
            void handleCurrencyFromOnly();
   */
};

} // namespace BY
} // namespace asarum
