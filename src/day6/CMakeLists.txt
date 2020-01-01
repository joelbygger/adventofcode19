
# Where the logic is.
new_cpp_library_shared(
        NAME orbits_lib
        SOURCES orbits.cpp orbits.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK false)

# For command line execution.
new_cpp_executable(
        NAME day6
        SOURCES main.cpp
        LINK_PRIVATE orbits_lib
        NO_CPPCHECK false)
