set(SOURCE_FILES kthminelement.cpp)
add_executable(kthminelement ${SOURCE_FILES})
target_include_directories(kthminelement PRIVATE ${PROJECT_SOURCE_DIR}/utils)

set(SOURCE_FILES sumassquares.cpp)
add_executable(sumassquares ${SOURCE_FILES})