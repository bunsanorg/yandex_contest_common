project(yandex_contest_common)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(BunsanCommon)

bunsan_use_boost(system filesystem serialization)

bunsan_use_bunsan(common)

bunsan_add_shared_library(${PROJECT_NAME}
    src/IntrusivePointeeBase.cpp
    src/Log.cpp
    src/Tempfile.cpp
    src/TypeInfo.cpp

    src/detail/IntrusivePointerHelper.cpp
    src/detail/LogOutputStream.cpp
    src/detail/StreamLog.cpp
    src/detail/ThrowingLog.cpp
    src/detail/NullLog.cpp
)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})
bunsan_install_plugins(BunsanCmake)

bunsan_include_tests()
