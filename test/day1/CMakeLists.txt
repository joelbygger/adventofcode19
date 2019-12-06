
new_cpp_executable(
        NAME day1_test
        SOURCES day1.cpp
        LINK_PUBLIC Catch2::Catch2 day1lib)

catch_discover_tests(day1_test)
