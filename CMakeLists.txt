cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

############# Generating Doxygen Documentation ##################

set(CMAKE_INSTALL_BINDIR /usr/local/bin)

project(tokenizer VERSION 1.0)
# using static versions of Boost libraries
set(Boost_USE_STATIC_LIBS ON)

add_subdirectory(${SRC_DIR})
add_subdirectory(${SRC_DIR}/dbConnect)

find_package(Boost COMPONENTS program_options REQUIRED)
add_executable(${EXEC} ${SRC_DIR}/main.cpp 
  ${SRC_DIR}/find_str_tfunc.cpp 
  ${SRC_DIR}/job.cpp 
  ${SRC_DIR}/job_proc.cpp 
  ${SRC_DIR}/tokenizer.cpp
  ${SRC_DIR}/job_group.cpp
  ${SRC_DIR}/menu.cpp
  ${SRC_DIR}/db_caller.cpp
  ${SRC_DIR}/db_queries.cpp
)

message("Boost Libs" ${Boost_INCLUDE_DIR})
target_include_directories(${EXEC} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${EXEC} ${Boost_LIBRARIES} dbConnect )

install(TARGETS ${EXEC}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
