set(SOURCE_FILES noncrooks.cpp)
add_executable(noncrooks ${SOURCE_FILES})
target_include_directories(noncrooks PRIVATE ${PROJECT_SOURCE_DIR}/utils)