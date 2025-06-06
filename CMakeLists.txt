cmake_minimum_required(VERSION 3.18)

project(cpp_inquirer_tools VERSION 0.0.1)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deps
#find_package(rcli REQUIRED)

set(CPP_INQUIRER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CPP_INQUIRER_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CPP_INQUIRER_IS_MAIN_PROJECT ON)
endif()

# target names
set(CPP_INQUIRER_LIB_NAME cpp_inquirer)
set(CPP_INQUIRER_LIB_VERSION 0.0.1)
set(CPP_INQUIRER_LIB_VERSION_MAJOR 0)
set(CPP_INQUIRER_VERSION ${PROJECT_VERSION})
set(CPP_INQUIRER_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library"
       ${CPP_INQUIRER_IS_MAIN_PROJECT})
option(CPP_INQUIRER_LIB_BUILD "Build cpp_inquirer lib" ON)
option(CPP_INQUIRER_LIB_INSTALL "Install cpp_inquirer lib" ${CPP_INQUIRER_IS_MAIN_PROJECT})

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPP_INQUIRER_TEST OFF)
endif()

if(CPP_INQUIRER_IS_MAIN_PROJECT)
  configure_file(${CPP_INQUIRER_SOURCE_DIR}/.templates/PKGBUILD.in
                 ${CPP_INQUIRER_SOURCE_DIR}/PKGBUILD @ONLY)

  configure_file(${CPP_INQUIRER_SOURCE_DIR}/.templates/install.sh.in
                 ${CPP_INQUIRER_SOURCE_DIR}/install.sh @ONLY)

  configure_file(${CPP_INQUIRER_SOURCE_DIR}/.templates/create-release.sh.in
                 ${CPP_INQUIRER_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${CPP_INQUIRER_SOURCE_DIR}/.templates/${CPP_INQUIRER_LIB_NAME}Config.hpp.in
    ${CPP_INQUIRER_SOURCE_DIR}/include/${CPP_INQUIRER_LIB_NAME}/${CPP_INQUIRER_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${CPP_INQUIRER_SOURCE_DIR}/sources/*.cpp"
       "${CPP_INQUIRER_SOURCE_DIR}/include/cpp_inquirer/*.hpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    C++ inquirer
)
include(CPack)
