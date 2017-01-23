
set(SOURCE_FILES close_enough.cpp)
add_executable(close_enough ${SOURCE_FILES})

set(SOURCE_FILES close_enough_enable_if.cpp)
add_executable(close_enough_enable_if ${SOURCE_FILES})

set(SOURCE_FILES example_single_responsibility.cpp)
add_executable(example_single_responsibility ${SOURCE_FILES})

set(SOURCE_FILES example_single_responsibility_revisited.cpp)
add_executable(example_single_responsibility_revisited ${SOURCE_FILES})

set(SOURCE_FILES example_two_responsibilities.cpp)
add_executable(example_two_responsibilities ${SOURCE_FILES})

set(SOURCE_FILES example_two_responsibilities_revisited.cpp)
add_executable(example_two_responsibilities_revisited ${SOURCE_FILES})

set(SOURCE_FILES f_of_v_copy.cpp)
add_executable(f_of_v_copy ${SOURCE_FILES})

set(SOURCE_FILES f_of_v_move.cpp)
add_executable(f_of_v_move ${SOURCE_FILES})

set(SOURCE_FILES f_of_v_ref.cpp)
add_executable(f_of_v_ref ${SOURCE_FILES})

set(SOURCE_FILES grade.cpp)
add_executable(grade ${SOURCE_FILES})

set(SOURCE_FILES lexical_cast.cpp)
add_executable(lexical_cast ${SOURCE_FILES})

set(SOURCE_FILES lookup_table.cpp)
add_executable(lookup_table ${SOURCE_FILES})

set(SOURCE_FILES ptr_manual_mgmt_2.cpp)
add_executable(ptr_manual_mgmt_2 ${SOURCE_FILES})

set(SOURCE_FILES ptr_manual_mgmt.cpp)
add_executable(ptr_manual_mgmt ${SOURCE_FILES})

set(SOURCE_FILES ptr_unique_ptr_mgmt_2.cpp)
add_executable(ptr_unique_ptr_mgmt_2 ${SOURCE_FILES})

set(SOURCE_FILES ptr_unique_ptr_mgmt.cpp)
add_executable(ptr_unique_ptr_mgmt ${SOURCE_FILES})

set(SOURCE_FILES small_program_make_unique.cpp)
add_executable(small_program_make_unique ${SOURCE_FILES})

set(SOURCE_FILES small_program_manual_ptr.cpp)
add_executable(small_program_manual_ptr ${SOURCE_FILES})

set(SOURCE_FILES small_program_unique_ptr.cpp)
add_executable(small_program_unique_ptr ${SOURCE_FILES})

set(SOURCE_FILES unique_ptr_comparisons_2.cpp)
add_executable(unique_ptr_comparisons_2 ${SOURCE_FILES})

set(SOURCE_FILES unique_ptr_comparisons.cpp)
add_executable(unique_ptr_comparisons ${SOURCE_FILES})

set(SOURCE_FILES unique_ptr_functor_deleter.cpp)
add_executable(unique_ptr_functor_deleter ${SOURCE_FILES})

set(SOURCE_FILES variadic_print_naive.cpp)
add_executable(variadic_print_naive ${SOURCE_FILES})

set(SOURCE_FILES variadic_printsz_naive.cpp)
add_executable(variadic_printsz_naive ${SOURCE_FILES})

set(SOURCE_FILES variadic_printsz_ok.cpp)
add_executable(variadic_printsz_ok ${SOURCE_FILES})

set(SOURCE_FILES variadic_printsz_oops.cpp)
add_executable(variadic_printsz_oops ${SOURCE_FILES})

set(SOURCE_FILES vector_unique_ptr_cost.cpp)
add_executable(vector_unique_ptr_cost ${SOURCE_FILES})
target_include_directories(vector_unique_ptr_cost PRIVATE ${PROJECT_SOURCE_DIR}/utils)

set(SOURCE_FILES mymvno.cpp)
add_executable(mymvno ${SOURCE_FILES})
target_include_directories(mymvno PRIVATE ${PROJECT_SOURCE_DIR}/utils)

set(SOURCE_FILES table.cpp)
add_executable(table ${SOURCE_FILES})
target_include_directories(table PRIVATE ${PROJECT_SOURCE_DIR}/utils)
