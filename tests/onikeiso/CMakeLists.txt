enable_testing()

FILE(GLOB GATES_TEST_FILES gates.test.c)
add_executable(onikeiso_gates_test ${GATES_TEST_FILES})
target_link_libraries(onikeiso_gates_test unity onikeiso)
target_include_directories(onikeiso_gates_test PUBLIC "${CMAKE_SOURCE_DIR}/src/onikeiso")
add_test(NAME onikeiso_gates_test COMMAND onikeiso_gates_test)

FILE(GLOB QUEUE_TEST_FILES queue.test.c)
add_executable(onikeiso_queue_test ${QUEUE_TEST_FILES})
target_link_libraries(onikeiso_queue_test unity onikeiso)
target_include_directories(onikeiso_queue_test PUBLIC "${CMAKE_SOURCE_DIR}/src/onikeiso")
add_test(NAME onikeiso_queue_test COMMAND onikeiso_queue_test)

FILE(GLOB BFS_TEST_FILES bfs.test.c)
add_executable(onikeiso_bfs_test ${BFS_TEST_FILES})
target_link_libraries(onikeiso_bfs_test unity onikeiso)
target_include_directories(onikeiso_bfs_test PUBLIC "${CMAKE_SOURCE_DIR}/src/onikeiso")
add_test(NAME onikeiso_bfs_test COMMAND onikeiso_bfs_test)
