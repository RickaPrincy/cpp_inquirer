add_executable(example main.cpp)

target_include_directories(example PRIVATE ${CPP_INQUIRER_SOURCE_DIR}/include)
target_link_directories(example PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(example PRIVATE cpp_inquirer)

set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                         "${CMAKE_BINARY_DIR}/bin")
