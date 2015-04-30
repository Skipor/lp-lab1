#####################################################################
# Helper functions
#####################################################################
function(add_gtest name)
  add_executable(${name} ${ARGN} )
  add_test(NAME ${name} COMMAND ${name})
  target_link_libraries(${name} gtest_main)
endfunction()


#####################################################################
# Basic setings
#####################################################################

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

#####################################################################
# Tests
#####################################################################



add_gtest(correct_parse_test correct_parse_test.cpp)
add_gtest(exeption_cases_test exception_cases_test.cpp)
