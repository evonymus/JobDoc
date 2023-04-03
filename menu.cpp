#include "menu.h"
#include "job_proc.h"

#include <iostream>

namespace by = asarum::BY;

by::Menu::Menu( int argc,  char *argv[])
    : m_generic_options("Generic Options"), m_code_options("Code Generation"),
      m_doc_options("Docs Generation"), m_cmd_line_options(),
      m_visible_options("Allowed Options"), m_pos_options() {

  initMenu(argc, argv);
}

void by::Menu::initMenu( int argc,  char *argv[]) {
  initGenericOptions();
  initCodeOptions();
  initDocOptions();

  m_visible_options.add(m_generic_options)
      .add(m_code_options)
      .add(m_doc_options);
  m_pos_options.add("file", -1);

  m_cmd_line_options.add(m_generic_options)
      .add(m_code_options)
      .add(m_doc_options);

  po::store(po::command_line_parser(argc, argv)
                .options(m_cmd_line_options)
                .positional(m_pos_options)
                .run(),
            m_var_map);
  // setting default path
  m_path = "./";
}

void by::Menu::handleMenu() {
  po::notify(m_var_map);

  if(m_var_map.empty()) {
    handleHelp();
  }

  if(m_var_map.count("help")) {
    handleHelp();
  }

  if(m_var_map.count("file") > 0 && m_var_map.count("code") > 0) {
    handleCodeGeneration();
  }
  if(m_var_map.count("file") > 0 && m_var_map.count("doc") > 0) {
    handleDocsGeneration();
  }
}

//------ PRIVATE FUNCTIONS ----------------------------

void by::Menu::initGenericOptions() {
  m_generic_options.add_options()
    ("version,v", "print version string")
    ( "help,h", "print help message")
    ("path,p", po::value<std::string>(&m_path), "(optional) path to store results")
    ("file,f", po::value<std::string>(&m_file_name), "the file to process")
    ;
}

void by::Menu::initCodeOptions() {
  m_code_options.add_options()("code,c", "generate code")(
      "summary,s", "generate job sumary documents");
}

void by::Menu::initDocOptions() {
  m_doc_options.add_options()("single,D", "documentation in a single file")(
      "doc,d", "document per job");
}

// ------------- handlers ----------

void by::Menu::handleCodeGeneration() {
  if(m_var_map.count("file") > 0 && m_var_map.count("code") > 0) {
    by::JobProc jobProc;
    jobProc.processFile(m_file_name.c_str());
    jobProc.exportJobs(m_path);
  }
}

void by::Menu::handleDocsGeneration() {

  if(m_var_map.count("file") > 0 && m_var_map.count("doc") > 0) {
    by::JobProc jobProc;
    jobProc.processFile(m_file_name.c_str());
    jobProc.exportDocs(m_path);
  }
}

void by::Menu::handleHelp() {
  std::cout << "usage jobdoc -f fileName -c | -j | -s \n\n"
    << m_visible_options <<std::endl;
}
