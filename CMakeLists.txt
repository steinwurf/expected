cmake_minimum_required(VERSION 3.10)
project(expected)

find_package(Python COMPONENTS Interpreter)

# Use waf to resolve dependencies
if(NOT DEFINED STEINWURF_RESOLVE)
  message(STATUS "Resolving dependencies...")
  execute_process(
    COMMAND ${Python_EXECUTABLE} waf resolve ${STEINWURF_RESOLVE_OPTIONS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE STATUS)

  if(STATUS AND NOT STATUS EQUAL 0)
    message(FATAL_ERROR "Failed: ${STATUS}")
  endif()

  set(STEINWURF_RESOLVE "${CMAKE_CURRENT_SOURCE_DIR}/resolve_symlinks")
endif()

# Define library
add_library(expected INTERFACE)
target_compile_features(expected INTERFACE cxx_std_11)

target_include_directories(expected
  INTERFACE "${STEINWURF_RESOLVE}/expected-source/include")

add_library(steinwurf::expected ALIAS expected)

# Install headers
install(
  DIRECTORY "${STEINWURF_RESOLVE}/expected-source/include"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING
  PATTERN *.hpp)

# Is top level project?
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  # Build executables
  add_executable(example_expected example/main.cpp)
  target_link_libraries(example_expected expected)

  enable_testing()
  add_test(example_expected example_expected)
endif()
