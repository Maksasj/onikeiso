# onikeiso target
FILE(GLOB SRC_FILES *.c)
add_library(onikeiso STATIC ${SRC_FILES})

# onikeiso_tests target
FILE(GLOB TEST_FILES *.test.c)
add_executable(onikeiso_tests ${TEST_FILES})
target_link_libraries(onikeiso_tests unity)
add_test(NAME onikeiso COMMAND onikeiso_tests)
