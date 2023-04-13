cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")

############# Generating Doxygen Documentation ##################

set(CMAKE_INSTALL_BINDIR /usr/local/bin)

project(tokenizer VERSION 1.0)
# using static versions of Boost libraries
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)
add_executable(${EXEC} main.cpp find_str_tfunc.cpp 
  job.cpp 
  job_proc.cpp 
  tokenizer.cpp
  job_group.cpp
  menu.cpp
  )

message("Boost Libs" ${Boost_INCLUDE_DIR})
target_include_directories(${EXEC} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${EXEC} ${Boost_LIBRARIES} -static)

install(TARGETS ${EXEC}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
