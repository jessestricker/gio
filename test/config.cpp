#include <gio/config.hpp>

#include "catch/catch.hpp"

TEST_CASE("config: the version number is not empty") {
  REQUIRE_FALSE(gio::version_major.empty());
  REQUIRE_FALSE(gio::version_minor.empty());
  REQUIRE_FALSE(gio::version_patch.empty());
}
