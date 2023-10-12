cmake_minimum_required(VERSION 3.25.1)

# Set project name and version.
set(PROJECT_NAME "chromalib")
file(STRINGS VERSION CURRENT_VERSION)
project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

# Set dependency paths.
set(GOOGLETEST_DIR "${CMAKE_BINARY_DIR}/dependencies/googletest")
set(JUCE_DIR "${CMAKE_BINARY_DIR}/dependencies/JUCE")


# Install googletest

if(NOT EXISTS ${GOOGLETEST_DIR})
    execute_process(
        COMMAND git clone https://github.com/google/googletest.git ${GOOGLETEST_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )
    if(result)
        message(FATAL_ERROR "Failed to clone Google Test: ${output}")
    endif()
endif()


# Install JUCE framework

if(NOT EXISTS ${JUCE_DIR})
    execute_process(
        COMMAND git clone https://github.com/juce-framework/JUCE.git ${JUCE_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )
    if(result)
        message(FATAL_ERROR "Failed to clone JUCE: ${output}")
    endif()
endif()


# Include dependencies
add_subdirectory(${JUCE_DIR})
add_subdirectory(${GOOGLETEST_DIR})
include_directories("chromalib/include/")

add_definitions(-DDONT_SET_USING_JUCE_NAMESPACE)

add_subdirectory(tests)