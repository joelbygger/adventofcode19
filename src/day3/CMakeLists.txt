
# Where the logic is.
new_cpp_library_shared(
        NAME routes_dist_lib
        SOURCES routes.cpp routes.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        NO_CPPCHECK false)

# For command line execution.
new_cpp_executable(
        NAME day3
        SOURCES main.cpp
        LINK_PRIVATE routes_dist_lib
        NO_CPPCHECK false)
