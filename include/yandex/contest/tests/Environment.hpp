#pragma once

#include <cstdlib>

#include <boost/filesystem/path.hpp>

static const boost::filesystem::path sourceDir = getenv("YANDEX_CONTEST_SOURCE_DIR");
static const boost::filesystem::path binaryDir = getenv("YANDEX_CONTEST_BINARY_DIR");
static const boost::filesystem::path testsSourceDir = sourceDir / "tests";
static const boost::filesystem::path testsBinaryDir = binaryDir / "tests";
static const boost::filesystem::path testsResourcesSourceDir = testsSourceDir / "resources";
static const boost::filesystem::path testsResourcesBinaryDir = testsBinaryDir / "resources";
