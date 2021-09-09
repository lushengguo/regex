add_library(nfa SHARED regexp.cpp nfa2.cpp)
add_library(lib::nfa ALIAS nfa)

add_executable(nfa_test nfa2_test.cpp)
target_link_libraries(nfa_test lib::nfa)

add_executable(util_test util_test.cpp)
