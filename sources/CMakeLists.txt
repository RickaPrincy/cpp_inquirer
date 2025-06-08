project(${CPP_INQUIRER_LIB_NAME} VERSION ${CPP_INQUIRER_LIB_VERSION} LANGUAGES CXX)

set(LIB_SOURCES 
  cpp_inquirer.cpp
  question.cpp
  text_question.cpp
  boolean_question.cpp
  select_question.cpp
  question_builder.cpp
  question_factory.cpp
  validator.cpp
  evaluate.cpp
  validator_factory.cpp
  callback.cpp
  utils.cpp
)

# Create the library
if(BUILD_SHARED_LIBS)
  add_library(${CPP_INQUIRER_LIB_NAME} SHARED ${LIB_SOURCES})
else()
  add_library(${CPP_INQUIRER_LIB_NAME} STATIC ${LIB_SOURCES})
endif()

# Set include directories for the library
target_include_directories(
  ${CPP_INQUIRER_LIB_NAME} PRIVATE $<BUILD_INTERFACE:${CPP_INQUIRER_SOURCE_DIR}/include>)

# target_link
#target_link_libraries(${CPP_INQUIRER_LIB_NAME} PUBLIC cpp_inquirer)

# set properties
set_target_properties(
  ${CPP_INQUIRER_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             SOVERSION ${CPP_INQUIRER_LIB_VERSION_MAJOR}
             VERSION ${CPP_INQUIRER_LIB_VERSION})

# lib install configuration
if(CPP_INQUIRER_LIB_INSTALL)
  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${CPP_INQUIRER_LIB_NAME}Version.cmake
    VERSION ${CPP_INQUIRER_VERSION}
    COMPATIBILITY SameMajorVersion)

  include(GNUInstallDirs)
  install(DIRECTORY ${CPP_INQUIRER_SOURCE_DIR}/include/${CPP_INQUIRER_LIB_NAME}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    TARGETS ${CPP_INQUIRER_LIB_NAME}
    EXPORT ${CPP_INQUIRER_LIB_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

  # Install the Config and ConfigVersion files
  install(
    EXPORT ${CPP_INQUIRER_LIB_NAME}Targets
    FILE ${CPP_INQUIRER_LIB_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_INQUIRER_LIB_NAME})

  configure_file(${CPP_INQUIRER_SOURCE_DIR}/cmake/${CPP_INQUIRER_LIB_NAME}Config.cmake.in
                 ${CMAKE_BINARY_DIR}/cmake/${CPP_INQUIRER_LIB_NAME}Config.cmake @ONLY)
  # Install the Config, ConfigVersion, and custom Find module files
  install(FILES ${CMAKE_BINARY_DIR}/cmake/${CPP_INQUIRER_LIB_NAME}Config.cmake
                ${CMAKE_BINARY_DIR}/cmake/${CPP_INQUIRER_LIB_NAME}Version.cmake
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_INQUIRER_LIB_NAME})
endif()
