
set(SOURCE_FILES manual-begin-end.cpp)
add_executable(manual-begin-end ${SOURCE_FILES})

set(SOURCE_FILES std-begin-end.cpp)
add_executable(std-begin-end ${SOURCE_FILES})

set(SOURCE_FILES size.cpp)
add_executable(size ${SOURCE_FILES})

set(SOURCE_FILES ex01.cpp)
add_executable(ex01 ${SOURCE_FILES})
target_include_directories(ex01 PRIVATE ${PROJECT_SOURCE_DIR}/utils)