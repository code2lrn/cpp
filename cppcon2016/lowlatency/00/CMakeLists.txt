find_package (Threads)

set(SOURCE_FILES pull.cpp)
add_executable(pull ${SOURCE_FILES})
target_link_libraries (pull ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES test.cpp)
add_executable(testcpp ${SOURCE_FILES})
target_link_libraries (testcpp ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES push.cpp)
add_executable(push ${SOURCE_FILES})
target_link_libraries (push ${CMAKE_THREAD_LIBS_INIT})
