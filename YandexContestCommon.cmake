# compiler
if(${CMAKE_COMPILER_IS_GNUCXX})
    set(gxx_flags "-std=c++11 -Wall -Wextra -Wno-multichar")
    if(${UNIX})
        set(gxx_flags "-pthread ${gxx_flags}")
    endif()
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${gxx_flags}")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 ${gxx_flags}")
endif()

if (${CMAKE_COMPILER_IS_GNUCC})
    set(gcc_flags "-std=c11 -Wall -Wextra")
    if(${UNIX})
        set(gcc_flags "-pthread ${gcc_flags}")
    endif()
    set(CMAKE_C_FLAGS_DEBUG "-g ${gcc_flags}")
    set(CMAKE_C_FLAGS_RELEASE "-O2 ${gcc_flags}")
endif()

include(${CMAKE_SOURCE_DIR}/user-config.cmake OPTIONAL)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

if(NOT DEFINED ENABLE_TESTS)
    set(ENABLE_TESTS ON CACHE BOOL "Do you want to enable testing?" FORCE)
endif()

# RPATH

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH false)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH false)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

# testing
macro(yandex_contest_tests)
    if(${ENABLE_TESTS})
        enable_testing()
        add_subdirectory(tests ${PROJECT_BINARY_DIR}/tests)
    endif()
endmacro()

macro(yandex_contest_tests_cmake)
    project(${PROJECT_NAME}_tests)

    cmake_minimum_required(VERSION 2.8)

    message("tests were included")

    aux_source_directory(. test_srcs)

    add_definitions(-DBOOST_TEST_DYN_LINK)

    foreach(src ${test_srcs})
        string(REGEX REPLACE "^.*/([^/]+)\\.cpp$" "\\1" trgt ${src})
        add_executable(test_${trgt} ${src})
        target_link_libraries(test_${trgt} ${CMAKE_PROJECT_NAME} ${libraries})
        add_test(${trgt} test_${trgt})
    endforeach()
endmacro()
