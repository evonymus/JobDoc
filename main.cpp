#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector> 
#include <memory>
#include <iostream>
#include <sstream>
#include <exception>

#include "job.h"
#include "job_proc.h"

namespace by = asarum::BY;
const char* FILE_NAME = "sdl_jobs_2023-02-03.dsv";


int main(int argc, char *argv[]) {
  try {
    by::JobProc jobProc;
    jobProc.processFile(FILE_NAME);
    //jobProc.exportJobs("/tmp/MD");
    jobProc.exportDocs("/tmp/MD");

  } 
  catch(std::exception &ex) {
    std::cout << "exception thrown: " << ex.what() << std::endl;
  }
  catch (...) {
    std::cout << "unexpected exception, closing the program \n";
  }
  return 0;
}
