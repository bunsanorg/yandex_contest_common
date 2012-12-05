project(yandex_contest_common)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/YandexContestCommon.cmake)

bunsan_use_boost(system filesystem serialization unit_test_framework)

bunsan_use_bunsan(common)

bunsan_add_shared_library(${PROJECT_NAME}
    src/Error.cpp
    src/Log.cpp
    src/Tempfile.cpp
    src/SystemError.cpp
    src/TypeInfo.cpp
    src/detail/LogOutputStream.cpp
    src/detail/StreamLog.cpp
    src/detail/ThrowingLog.cpp
    src/detail/NullLog.cpp
)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})
install(FILES YandexContestCommon.cmake DESTINATION ${CMAKE_ROOT}/Modules)

bunsan_include_tests()
