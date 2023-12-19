# onikeiso_tests target
FILE(GLOB TEST_FILES *.test.c)
add_executable(onikeiso_tests ${TEST_FILES})
target_link_libraries(onikeiso_tests unity onikeiso)
target_include_directories(onikeiso_tests PUBLIC "${CMAKE_SOURCE_DIR}/src/onikeiso")
add_test(NAME onikeiso COMMAND onikeiso_tests)
