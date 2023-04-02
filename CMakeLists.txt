cmake_minimum_required(VERSION 3.10)
#################################
# Generate Docs
#################################
OPTION(BUILD_WITH_DOCS "Generate Docs" ON)
IF(TASKSCH_BUILD_WITH_DOCS)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/docs)
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(tokenizer VERSION 1.0)
add_executable(run main.cpp find_str_tfunc.cpp 
  job.cpp 
  job_proc.cpp 
  tokenizer.cpp
  job_group.cpp
  )
