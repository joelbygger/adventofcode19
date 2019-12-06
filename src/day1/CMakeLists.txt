
# Where the logic is.
new_cpp_library_shared(
        NAME day1lib
        SOURCES fuel.cpp fuel.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK true)

# For command line execution.
new_cpp_executable(
        NAME day1
        SOURCES main.cpp
        LINK_PRIVATE day1lib
        NO_CPPCHECK true)
