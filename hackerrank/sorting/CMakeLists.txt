
# https://www.hackerrank.com/challenges/almost-sorted
#
set(SOURCE_FILES almostsorted.cpp)
add_executable(almostsorted ${SOURCE_FILES})

# Sort Demo
# Quick Sort and Hap Sort
#
set(SOURCE_FILES sortdemo.cpp)
add_executable(sortdemo ${SOURCE_FILES})
target_include_directories(sortdemo PRIVATE ${PROJECT_SOURCE_DIR}/utils)
