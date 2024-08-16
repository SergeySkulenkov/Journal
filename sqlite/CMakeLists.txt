
add_library(sqlite3 STATIC
 sqlite3.c
 sqlite3.h
)

target_include_directories(sqlite3
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PUBLIC $<INSTALL_INTERFACE:include/>)
