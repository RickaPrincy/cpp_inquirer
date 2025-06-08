cmake_minimum_required(VERSION 3.18)

project(cpp_inquirer_tools VERSION 0.0.1)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
option(BUILD_SHARED_LIBS "Build cpp_inquirer as a shared library" OFF)
option(CPP_INQUIRER_LIB_BUILD "Build cpp_inquirer lib" ON)
option(CPP_INQUIRER_LIB_INSTALL "Install cpp_inquirer lib" ${CPP_INQUIRER_IS_MAIN_PROJECT})
option(CPP_INQUIRER_BUILD_EXAMPLE "Build the examples in the project" ${CPP_INQUIRER_IS_MAIN_PROJECT})

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

if(NOT CMAKE_BUILD_SHARED_LIBS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

add_subdirectory(sources)

if(CPP_INQUIRER_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    C++ inquirer
)
include(CPack)

# clang-format
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES
     "${CPP_INQUIRER_SOURCE_DIR}/sources/*.cpp"
     "${CPP_INQUIRER_SOURCE_DIR}/sources/*.hpp"
     "${CPP_INQUIRER_SOURCE_DIR}/include/cpp_inquirer/*.hpp")

  add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format to format code"
  )

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run --Werror -style=file ${ALL_SOURCE_FILES}
    COMMENT "Checking code format (clang-format) - will fail if formatting issues"
  )
else()
  message(WARNING "clang-format not found. Format targets will NOT be available.")
endif()

# clang-tidy
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
  if(NOT ALL_SOURCE_FILES)
    file(GLOB_RECURSE ALL_SOURCE_FILES
       "${CPP_INQUIRER_SOURCE_DIR}/sources/*.cpp"
       "${CPP_INQUIRER_SOURCE_DIR}/sources/*.hpp"
       "${CPP_INQUIRER_SOURCE_DIR}/include/cpp_inquirer/*.hpp")
  endif()
  
  add_custom_target(lint
    COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_CURRENT_BINARY_DIR} ${ALL_SOURCE_FILES}
    COMMENT "Running clang-tidy"
  )
else()
  message(WARNING "clang-tidy not found. clang-tidy target will NOT be available.")
endif()
