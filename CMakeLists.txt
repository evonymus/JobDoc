cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXEC "jobdoc")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# # # # # # # # # # ### Generating Doxygen Documentation ##################

set(CMAKE_INSTALL_BINDIR /usr/local/bin)

project(tokenizer VERSION 1.0)
# using static versions of Boost libraries
set(Boost_USE_STATIC_LIBS ON)

# add_subdirectory(${SRC_DIR}/GUI)

find_package(
  Boost
  COMPONENTS program_options filesystem
  REQUIRED)
find_package(PocoFoundation)
find_package(PocoData)
find_package(PocoDataSQLite)
add_executable(
  ${EXEC}
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/find_str_tfunc.cpp
  ${SRC_DIR}/job.cpp
  ${SRC_DIR}/job_proc.cpp
  ${SRC_DIR}/tokenizer.cpp
  ${SRC_DIR}/job_group.cpp
  ${SRC_DIR}/sqlite_connector.cpp
  ${SRC_DIR}/menu.cpp)

# add_executable(GuiDoc ${SRC_DIR}/GUI/gui_main.cpp)
# target_link_libraries(GuiDoc ${wxWidgets_LIBRARIES})

message("Boost Libs" ${Boost_INCLUDE_DIR})
target_include_directories(${EXEC} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${EXEC} ${Boost_LIBRARIES} PocoFoundation PocoData
                      PocoDataSQLite)

install(TARGETS ${EXEC} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
