
# Where the logic is.
new_cpp_library_shared(
        NAME intcode_lib
        SOURCES intcode.cpp intcode.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK false)

# For command line execution.
new_cpp_executable(
        NAME day2
        SOURCES main.cpp
        LINK_PRIVATE intcode_lib
        NO_CPPCHECK false)
