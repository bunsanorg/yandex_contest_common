#pragma once

#include <cstdlib>

#include <boost/filesystem/path.hpp>

static const boost::filesystem::path testsSourceDir = getenv("YANDEX_CONTEST_TESTS_SOURCE_DIR");
static const boost::filesystem::path testsBinaryDir = getenv("YANDEX_CONTEST_TESTS_BINARY_DIR");
static const boost::filesystem::path testsResourcesSourceDir = getenv("YANDEX_CONTEST_TESTS_RESOURCES_SOURCE_DIR");
static const boost::filesystem::path testsResourcesBinaryDir = getenv("YANDEX_CONTEST_TESTS_RESOURCES_BINARY_DIR");
