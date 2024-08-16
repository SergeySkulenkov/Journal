cmake_minimum_required(VERSION 3.5)

project(JournalApp)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(sqlite)
add_subdirectory(Journal)

# USE_FOLDERS group cmake generated projects into one (CMakePredefinedTargets) folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
