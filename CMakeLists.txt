cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# # # # # # # # # # ### Generating Doxygen Documentation ##################

#set(CMAKE_INSTALL_BINDIR /usr/local/bin)


project(Jobdoc VERSION 1.0)

# Boost settings
#set(Boost_USE_STATIC_LIBS ON)  # only find static libs

set(CMAKE_PREFIX_PATH "C:/dev/Libs/Poco" "C:/dev/Libs/Boost/boost")

set(CMAKE_BUILD_TYPE Release)

## the two options below control static linking of POCO
#add_definitions(-DPOCO_STATIC)
#option(BUILD_SHARED_LIBS OFF)

find_package(Boost 1.84 REQUIRED CONFIG HINTS c:/dev/libs/boost/lib/cmake/boost-1.85.0)
if(Boost_FOUND) 
  message("Boost_INCLUDE_DIRS=${Boost_INLCUDE_DIRS}")
  message("Boost_COMPILER=${Boost_COMPILER}")
endif()
find_package(Poco REQUIRED COMPONENTS Foundation Data DataSQLite)
#find_package(Boost REQUIRED COMPONENTS filesystem program_options HINTS "c:/dev/libs/boost/stage/lib/cmake" )
find_package(Boost REQUIRED COMPONENTS filesystem program_options )

add_executable( ${EXEC} 
  ${SRC_DIR}/jobdoc.cpp
  ${SRC_DIR}/find_str_tfunc.cpp
  ${SRC_DIR}/job.cpp
  ${SRC_DIR}/job_proc.cpp
  ${SRC_DIR}/tokenizer.cpp
  ${SRC_DIR}/job_group.cpp
  ${SRC_DIR}/sqlite_connector.cpp
  ${SRC_DIR}/menu.cpp)

set(POCO_LIB_DIR c:/dev/libs/poco/lib)
#include_directories(${POCO_INCLUDE_DIR})
#find_library(POCO_LIB_DIR PocoFoundation PocoData PocoDataSQLite PATHS ${POCO_LIB_DIR})
#link_directories(${POCO_LIB_DIR})
#target_include_directories(${EXEC} PRIVATE  ${Boost_INCLUDE_DIR})
target_link_libraries(${EXEC} PRIVATE ${Boost_LIBRARIES} Poco::Foundation Poco::Data Poco::DataSQLite )

#target_link_libraries(${EXEC} PRIVATE ${Boost_LIBRARIES} 
#${POCO_LIB_DIR}/PocoFoundationmd.lib 
#${POCO_LIB_DIR}/PocoDatamd.lib 
#${POCO_LIB_DIR}/PocoDataSQLitemd.lib)

install(TARGETS ${EXEC} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
