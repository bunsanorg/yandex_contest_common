#pragma once

#include "bunsan/tests/environment.hpp"

static const boost::filesystem::path sourceDir = bunsan::tests::dir::source;
static const boost::filesystem::path binaryDir = bunsan::tests::dir::binary;
static const boost::filesystem::path testsSourceDir = bunsan::tests::dir::tests::source;
static const boost::filesystem::path testsBinaryDir = bunsan::tests::dir::tests::binary;
static const boost::filesystem::path testsResourcesSourceDir = testsSourceDir / "resources";
static const boost::filesystem::path testsResourcesBinaryDir = testsBinaryDir / "resources";
