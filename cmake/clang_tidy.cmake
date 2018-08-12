###
# This file will find clang tidy, set up some useful variables and create helper 
# functions that are useful when creating new build targets.
###

find_program( CLANG_TIDY_EXE
    NAMES clang-tidy clang-tidy-6.0
    DOC "Path to clang-tidy executeable." )

###
# A helper function, extracts the clang-tidy version from the found binary.
###
function(find_clang_tidy_version VAR)
    execute_process(COMMAND ${CLANG_TIDY_EXE} -version OUTPUT_VARIABLE VERSION_OUTPUT)
    separate_arguments(VERSION_OUTPUT_LIST UNIX_COMMAND "${VERSION_OUTPUT}")
    list(FIND VERSION_OUTPUT_LIST "version" VERSION_INDEX)
    if(VERSION_INDEX GREATER 0)
        math(EXPR VERSION_INDEX "${VERSION_INDEX} + 1")
        list(GET VERSION_OUTPUT_LIST ${VERSION_INDEX} VERSION)
        set(${VAR} ${VERSION} PARENT_SCOPE)
    else()
        set(${VAR} "0.0" PARENT_SCOPE)
    endif()
endfunction()

###
# If clang-tidy was found, configure some variables.
###
if(NOT CLANG_TIDY_EXE)
    message("---- Could not find clang-tidy, you won't get a build target to run clang-tidy.")
else()
    find_clang_tidy_version(CLANG_TIDY_VERSION)
    # Older/ newer versions should work, I just have this check beacuse this is the version verified to work.
    if (${CLANG_TIDY_VERSION} VERSION_LESS "6.0.0")
        message("---- Clang-tidy was found, but in a version I am not sure will work, no build target for this will be added, found version: " ${CLANG_TIDY_VERSION})
    endif()
    
    # Uncomment to allow clang-tidy to fix the suggestions inline, automagically.
    #set(CLANG_TIDY_FLAGS "-fix")

    # Enable all checks.
    set(CLANG_TIDY_CHECKS "*")

    # Manually disable individual checks, with accompanying comment. This is waht I've seen, 
    # if it makes sense in your codebase, or if I've missed any, is up to you.
    # A good check, but disabled in THIS project because I don't want to fix it right now.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-cppcoreguidelines-pro-bounds-pointer-arithmetic")
    # Default arguments are ok.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-fuchsia-default-arguments")
    # We don't need this style.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-llvm-header-guard")
    # I don't think this is needed for THIS project, I only got complaints on constructors.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-hicpp-explicit-conversions")
    # I think it's good with const in function declaration.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-readability-avoid-const-params-in-decls")
    # I've only received warning on non-const reference parameters to functions, which I think i s fine.
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-runtime-references")
    # TODO should I have this? Same as hicpp-explicit-conversions? Explicit on all constructors with one param?
    set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-explicit-constructor")

endif()


###
# Adds clang-tidy to an executeable, can handle both GCC ang Clang as target compiler.
# - For Clang, uses clang-tidy integration in CMake, will be executed on each compile.
# - For GCC. adds a new target that only runs clang-tidy. Because Clang will see GCC
#   flags (via compilation database) and complain on them at every compile, annoying.
#   We'll still get complaints on the GCC flags, but only when target is executed.
#   We'll get color highlighting on output (only works with Make?).
###
function(add_clang_tidy_to_target)
    # Extract function params.
    set(options )
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_PRIVATE)
    cmake_parse_arguments(TARGET_TIDY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(CLANG_TIDY_EXE)
        if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            set(TARGET_NAME ${TARGET_TIDY_NAME}_clang_tidy)
            #message("---- Adding new clang-tidy target ${TARGET_NAME} with sources: [${TARGET_TIDY_SOURCES}] and includes [${TARGET_TIDY_INCLUDE_PRIVATE}]")
            # Formatting.
            foreach(SRC ${TARGET_TIDY_SOURCES})
                list(APPEND SRC_W_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${SRC})
            endforeach()
            foreach(inc ${TARGET_TIDY_INCLUDE_PRIVATE})
                list(APPEND ALL_INCLUDES "-I${CMAKE_CURRENT_SOURCE_DIR}/${inc}")
            endforeach()

            add_custom_target(${TARGET_NAME}
                COMMAND ${CLANG_TIDY_EXE}
                -p ${CMAKE_BINARY_DIR} # Locaction of the compile commands, enabled with CMAKE_EXPORT_COMPILE_COMMANDS.
                -header-filter=.*
                --checks="${CLANG_TIDY_CHECKS}"
                ${CLANG_TIDY_FLAGS}
                ${SRC_W_PATH}
                --
                ${ALL_INCLUDES})

        elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=${CLANG_TIDY_CHECKS}" "-header-filter=.*" "${CLANG_TIDY_FLAGS}")
            # We could have set variable CMAKE_CXX_CLANG_TIDY, but then the 
            # property for tidy would be added to all targets, meaning there 
            # would be GCC warnings on compilation flags unknown to GCC, and 
            # perhaps to targets where we don't want tidy.
            # Therefore we set property CXX_CLANG_TIDY ourselves here.
            set_target_properties(
                ${TARGET_TIDY_NAME} PROPERTIES
                CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
            )
        endif()
    endif()
endfunction()