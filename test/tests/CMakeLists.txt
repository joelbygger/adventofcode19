
find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

new_cpp_library_shared(
        NAME test_base
        SOURCES test_base.cpp
        LINK_PUBLIC Catch2::Catch2)

new_cpp_executable(
        NAME day1_test
        SOURCES day1.cpp
        LINK_PUBLIC test_base fuel_lib)
catch_discover_tests(day1_test)

new_cpp_executable(
        NAME day2_test
        SOURCES day2.cpp
        LINK_PUBLIC test_base intcode_lib)
catch_discover_tests(day2_test)

new_cpp_executable(
        NAME day3_test
        SOURCES day3.cpp
        LINK_PUBLIC test_base routes_dist_lib)
catch_discover_tests(day3_test)

new_cpp_executable(
        NAME day4_test
        SOURCES day4.cpp
        LINK_PUBLIC test_base password_lib)
catch_discover_tests(day4_test)

new_cpp_executable(
        NAME day5_test
        SOURCES day5.cpp
        LINK_PUBLIC test_base intcode_lib2)
catch_discover_tests(day5_test)
