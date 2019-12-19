
# Where the logic is.
new_cpp_library_shared(
        NAME password_lib
        SOURCES password.cpp password.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK false)

# For command line execution.
new_cpp_executable(
        NAME day4
        SOURCES main.cpp
        LINK_PRIVATE password_lib
        NO_CPPCHECK false)
