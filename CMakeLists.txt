project(yandex_contest_common)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/YandexContestCommon.cmake)

# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system filesystem serialization unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND libraries ${Boost_LIBRARIES})

# Local
include_directories(include)

# Targets
add_library(${PROJECT_NAME} SHARED
    src/Error.cpp
    src/Log.cpp
    src/Tempfile.cpp
    src/SystemError.cpp
    src/detail/LogOutputStream.cpp
    src/detail/StreamLog.cpp
    src/detail/ThrowingLog.cpp
)
target_link_libraries(${PROJECT_NAME} ${libraries})

# Installation
install(DIRECTORY include DESTINATION .)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES YandexContestCommon.cmake DESTINATION ${CMAKE_ROOT}/Modules)

yandex_contest_tests()
