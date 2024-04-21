# cmake_minimum_required(VERSION 3.18)

find_library(soci_core "/usr/local/lib/soci_core.a")
find_library(soci_oracle "/usr/local/lib/soci_oracle.a")

add_library(dbConnect orcl-con-def.cpp connector.cpp)
# add_executable(run main.cpp orcl-con-def.cpp connector.cpp)
# set_target_properties(run PROPERTIES RUNTIME_OUTPUT_DIRECTORY
# "${CMAKE_BINARY_DIR}" )

target_link_libraries(dbConnect PRIVATE soci_core soci_oracle)
# target_link_libraries(dbConnect PRIVATE soci_core soci_oracle  )
