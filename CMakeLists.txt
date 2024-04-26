cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# # # # # # # # # # ### Generating Doxygen Documentation ##################

#set(CMAKE_INSTALL_BINDIR /usr/local/bin)


project(Jobdoc VERSION 1.0)

# Boost settings

set(POCO_ROOT c:/Dev/Libs/Poco)
set(Boost_ROOT c:/Dev/Libs/boost)

#set(Boost_USE_STATIC_LIBS ON)  # only find static libs
## the two options below control static linking of POCO
#add_definitions(-DPOCO_STATIC)
#option(BUILD_SHARED_LIBS OFF)

find_package(Boost  REQUIRED filesystem program_options)
if(Boost_FOUND) 
  message("Boost_INCLUDE_DIRS=${Boost_INLCUDE_DIRS}")
  message("Boost_COMPILER=${Boost_COMPILER}")
endif()
find_package(Poco REQUIRED COMPONENTS Foundation Data DataSQLite)
#find_package(Boost REQUIRED COMPONENTS filesystem program_options HINTS "c:/dev/libs/boost/stage/lib/cmake" )
find_package(Boost COMPONENTS filesystem program_options REQUIRED )

add_executable( ${EXEC} 
  ${SRC_DIR}/jobdoc.cpp
  ${SRC_DIR}/find_str_tfunc.cpp
  ${SRC_DIR}/job.cpp
  ${SRC_DIR}/job_proc.cpp
  ${SRC_DIR}/tokenizer.cpp
  ${SRC_DIR}/job_group.cpp
  ${SRC_DIR}/sqlite_connector.cpp
  ${SRC_DIR}/menu.cpp)

#find_library(POCO_LIB_DIR PocoFoundation PocoData PocoDataSQLite PATHS_SUFFIXES ${POCO_LIB_DIR})

target_include_directories(${EXEC} PRIVATE  ${Boost_INCLUDE_DIR} ${Poco_INCLUDE_DIR})

target_link_libraries(${EXEC} PRIVATE ${Boost_LIBRARIES} Poco::Foundation Poco::Data Poco::DataSQLite)

install(TARGETS ${EXEC} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
