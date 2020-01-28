#include "gio/bytes.hpp"

#include <algorithm>
#include <cstdint>
#include <type_traits>

#include "catch/catch.hpp"

TEST_CASE("bytes: const as-bytes() returns immutable iterators") {
  const auto value = std::uint16_t{0x1234};
  const auto bytes = gio::as_bytes(value);
  auto& first = *bytes.begin();
  STATIC_REQUIRE(std::is_const_v<std::remove_reference_t<decltype(first)>>);
}

TEST_CASE("bytes: non-const as-bytes() returns mutable iterators") {
  auto value = std::uint16_t{0x1234};
  const auto bytes = gio::as_bytes(value);
  auto& first = *bytes.begin();
  STATIC_REQUIRE_FALSE(std::is_const_v<std::remove_reference_t<decltype(first)>>);

  auto& second = *(bytes.begin() + 1);
  std::swap(first, second);
  REQUIRE(value == 0x3412);
}

TEST_CASE("bytes: byte span values correspond to data") {
  const auto src = std::uint16_t{0xaabb};
  const auto src_bytes = gio::as_bytes(src);
  auto dst = std::uint16_t{0};

  SECTION("data is in native order") {
    auto dst_bytes = gio::as_bytes<gio::NativeEndian>(dst);
    std::copy(src_bytes.begin(), src_bytes.end(), dst_bytes.begin());
    REQUIRE(dst == 0xaabb);
  }

  SECTION("data is in reversed order") {
    auto dst_bytes = gio::as_bytes<gio::detail::ReverseEndian>(dst);
    std::copy(src_bytes.begin(), src_bytes.end(), dst_bytes.begin());
    REQUIRE(dst == 0xbbaa);
  }
}
