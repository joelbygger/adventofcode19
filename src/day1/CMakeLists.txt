
# Where the logic is.
new_cpp_library_shared(
        NAME fuel_lib
        SOURCES fuel.cpp fuel.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK false)

# For command line execution.
new_cpp_executable(
        NAME day1
        SOURCES main.cpp
        LINK_PRIVATE fuel_lib
        NO_CPPCHECK false)
