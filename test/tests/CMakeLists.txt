
find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

#set( HEADER_DIR ${CATCH_DIR}/single_include )

#add_library(
#        CatchMain OBJECT 
#        test_base.cpp catch.hpp )

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
#new_cpp_executable(
#        NAME day1_test
#        SOURCES day1.cpp $<TARGET_OBJECTS:CatchMain> catch2/catch.hpp
#        INCLUDE_PRIVATE ${CATCH_DIR})
        #LINK_PUBLIC test_base day1_test_lib)# day2_test_lib)

# Where the logic is.
#new_cpp_library_shared(
 #       NAME test_base
  #      SOURCES test_base.cpp
   #     LINK_PUBLIC Catch2::Catch2)

#new_cpp_library_shared(
 #       NAME day1_test_lib
  #      SOURCES day1.cpp ${HEADER_DIR}/catch2/catch.hpp
   #     LINK_PRIVATE test_base fuel_lib)

#new_cpp_library_shared(
#        NAME day2_test_lib
#        SOURCES day2.cpp
#        LINK_PRIVATE intcode_lib)


#new_cpp_executable(
#        NAME tests
 #       SOURCES test_base.cpp
  #      LINK_PUBLIC test_base day1_test_lib)# day2_test_lib)
