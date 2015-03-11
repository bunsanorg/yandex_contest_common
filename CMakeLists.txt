cmake_minimum_required(VERSION 3.0)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

project(yandex_contest_common)

find_package(BunsanCMake CONFIG REQUIRED)

bunsan_add_library(${PROJECT_NAME}
    src/IntrusivePointeeBase.cpp
    src/Log.cpp
    src/Tempfile.cpp

    src/detail/IntrusivePointerHelper.cpp
    src/detail/LogOutputStream.cpp
    src/detail/StreamLog.cpp
    src/detail/ThrowingLog.cpp
    src/detail/NullLog.cpp
)
bunsan_use_bunsan_package(${PROJECT_NAME} bunsan_common bunsan_common)
bunsan_use_boost(${PROJECT_NAME} system filesystem serialization)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})
bunsan_install_project()

bunsan_include_tests()
