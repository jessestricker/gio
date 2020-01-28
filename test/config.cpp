#include "gio/config.hpp"

#include <cstddef>
#include <cstdint>

#include "catch/catch.hpp"

TEST_CASE("config: the version number is not empty") {
  REQUIRE_FALSE(gio::version_major.empty());
  REQUIRE_FALSE(gio::version_minor.empty());
  REQUIRE_FALSE(gio::version_patch.empty());
}

TEST_CASE("config: native endian is set correctly") {
  REQUIRE(gio::LittleEndian != gio::BigEndian);

  const auto test = std::uint16_t{0xaabb};
  const auto bytes = reinterpret_cast<const std::byte*>(&test);
  const auto bigEndian = (bytes[0] == std::byte{0xaa});

  if (bigEndian) {
    REQUIRE(gio::NativeEndian == gio::BigEndian);
  } else {
    REQUIRE(gio::NativeEndian == gio::LittleEndian);
  }
}
