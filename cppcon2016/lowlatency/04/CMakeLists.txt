find_package (Threads)

set(SOURCE_FILES callbacks.cpp)
add_executable(callbacks ${SOURCE_FILES})
target_include_directories(callbacks PRIVATE ${PROJECT_SOURCE_DIR}/utils)

set(SOURCE_FILES atomics.cpp)
add_executable(atomics ${SOURCE_FILES})
target_include_directories(atomics PRIVATE ${PROJECT_SOURCE_DIR}/utils)
target_link_libraries (atomics ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES mo.cpp)
add_executable(mo ${SOURCE_FILES})
