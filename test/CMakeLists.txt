#####################################################################
# Helper functions
#####################################################################
function(add_test_macro name)
  add_executable(${name} ${ARGN} )
  add_test(NAME ${name} COMMAND ${name})
  target_link_libraries(${name} hoard_common)
endfunction()

function(add_gtest name)
  add_test_macro(${name} ${ARGN} )
  target_link_libraries(${name} gtest_main)
endfunction()


#####################################################################
# Basic setings
#####################################################################
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#####################################################################
# Tests
#####################################################################



