cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
#set(CMAKE_TOOLCHAIN_FILE "C:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake" )

# # # # # # # # # # ### Generating Doxygen Documentation ##################

#set(CMAKE_INSTALL_BINDIR /usr/local/bin)

project(Jobdoc VERSION 1.0)
include_directories(${INCLUDE_DIR})
# Boost settings
set(CMAKE_BUILD_TYPE RELEASE)


#set(Boost_USE_STATIC_LIBS ON)  # only find static libs

## the two options below control static linking of POCO
#add_definitions(-DPOCO_STATIC)
#option(BUILD_SHARED_LIBS OFF)

#find_package(Boost  REQUIRED filesystem program_options)
find_package(Poco REQUIRED COMPONENTS  Data DataSQLite DataODBC ActiveRecord)
find_package(Boost REQUIRED COMPONENTS filesystem program_options algorithm )

link_directories("C:/Users/mdzie/Development/JobDoc/build/vcpkg_installed/x64-windows/lib")

add_executable( ${EXEC} 
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/FindStrTFunc.cpp
  ${SRC_DIR}/Tokenizer.cpp
  ${SRC_DIR}/SQLiteConnector.cpp
  ${SRC_DIR}/OdbcConnector.cpp
  ${SRC_DIR}/jobDef.cpp
  ${SRC_DIR}/JobSelCta.cpp
  ${SRC_DIR}/EntySelCta.cpp
  ${SRC_DIR}/AdtnData.cpp
  ${SRC_DIR}/SchdDetl.cpp
  ${SRC_DIR}/JobDefGetter.cpp
  ${SRC_DIR}/JobScriptWriter.cpp
  ${SRC_DIR}/DocWriter.cpp
  ${SRC_DIR}/DataCopier.cpp
  ${SRC_DIR}/CodeWriter.cpp
  ${SRC_DIR}/test.cpp
  ${SRC_DIR}/Menu.cpp
  ${SRC_DIR}/BaseConnector.cpp
  ${SRC_DIR}/Meter.cpp
  ${SRC_DIR}/EscValidator.cpp
)

set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"Poco:Poco::Foundationd\")

target_include_directories(${EXEC} PRIVATE  ${Boost_INCLUDE_DIR} ${Poco_INCLUDE_DIR})
#target_link_libraries(${EXEC} PRIVATE ${Boost_LIBRARIES}  Poco::Data Poco::DataSQLite Poco::DataODBC Poco::ActiveRecord)
target_link_libraries(${EXEC} PRIVATE optimized ${Boost_LIBRARIES} ${POCO_LIBRARIES})

install(TARGETS ${EXEC} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
