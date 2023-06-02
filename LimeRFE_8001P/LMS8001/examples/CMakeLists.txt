add_executable(LMS8_basic LMS8_basic.cpp)
set_target_properties(LMS8_basic PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(LMS8_basic LMS8API)